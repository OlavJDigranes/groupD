#include "LevelSystem.h"
#include <fstream>
#include <iostream>

#define DEBUG 1

using namespace std;
using namespace sf;

//Legend in shared documents
std::map<LevelSystem::Tile, sf::Color> LevelSystem::_colours{
    {EDGEWALL, Color(255, 0, 0, 255)}, 
    {HOME, Color(1, 69, 0, 255)}, 
    {CHECKPOINT, Color(4, 217, 0, 255)},
    {SHOPS, Color(183, 75, 25, 255)},
    {ROAD, Color(0, 0, 0, 255)},
    {EMPTY, Color(255, 255, 255, 255)}, 
    {BIRDSPAWN, Color(112, 62, 0, 255)}, 
    {CAR1SPAWN, Color(0, 246, 217, 255)},
    {CAR2SPAWN, Color(0, 48, 246, 255)},
    {CAR3SPAWN, Color(136, 3, 192, 255)},
    {TREE, Color(91, 114, 137, 255)}, //Slight modification to colour mapping for clarity, original is (91, 104, 127)
    {GRASS, Color(132, 216, 137, 255)}, 
    {GRATEROAD, Color(255, 142, 0, 255)}, 
    {NEIGHBOURHOUSE, Color(255, 251, 85, 255)}, 
    {EMPTYHOUSE, Color(254, 0 ,255, 255)}, 
    {PARKINGSPACE, Color(135, 135, 135, 255)}, 
    {AICHECKPOINT1, Color(0, 0, 0, 255)}, //Same colour as road
    {AICHECKPOINT2, Color(0, 0, 0, 255)}, //Same colour as road
    {AICHECKPOINT3, Color(0, 0, 0, 255)}, //Same colour as road
    {AICHECKPOINT4, Color(0, 0, 0, 255)}, //Same colour as road
    {AICHECKPOINT5, Color(0, 0, 0, 255)}  //Same colour as road
    
};

sf::Color LevelSystem::getColor(LevelSystem::Tile t) {
    auto it = _colours.find(t);
    if (it == _colours.end()) {
        _colours[t] = Color::Transparent;
    }
    return _colours[t];
}

void LevelSystem::setColor(LevelSystem::Tile t, sf::Color c) {
    _colours[t] = c;
}

std::unique_ptr<LevelSystem::Tile[]> LevelSystem::_tiles;
size_t LevelSystem::_width;
size_t LevelSystem::_height;
sf::RenderTexture LevelSystem::_mapTex;
sf::Sprite LevelSystem::_mapSprite;
sf::Vector2f LevelSystem::_mapMovement;

float LevelSystem::_tileSize(50.f);
Vector2f LevelSystem::_offset(0.0f, 30.0f);
// Vector2f LevelSystem::_offset(0,0);
vector<std::unique_ptr<sf::RectangleShape>> LevelSystem::_sprites;

void LevelSystem::loadLevelFile(const std::string& path, float tileSize) {
    _tileSize = tileSize;
    _mapSprite.setPosition(sf::Vector2f(0.f, 0.f));
    _mapMovement = sf::Vector2f(0.f, 0.f);
    size_t w = 0, h = 0;
    string buffer;

    // Load in file to buffer
    ifstream f(path);
    if (f.good()) {
        f.seekg(0, std::ios::end);
        buffer.resize(f.tellg());
        f.seekg(0);
        f.read(&buffer[0], buffer.size());
        f.close();
    }
    else {
        throw string("Couldn't open level file: ") + path;
    }

    std::vector<Tile> temp_tiles;
    int widthCheck = 0;
    for (int i = 0; i < buffer.size(); ++i) {
        const char c = buffer[i];
        if (c == '\0') { break; }
        if (c == '\n') { // newline
            if (w == 0) {  // if we haven't written width yet
                w = i;       // set width
            }
            else if (w != (widthCheck - 1)) {
                throw string("non uniform width:" + to_string(h) + " ") + path;
            }
            widthCheck = 0;
            h++; // increment height
        }
        else {
            temp_tiles.push_back((Tile)c);
        }
        ++widthCheck;
    }

    if (temp_tiles.size() != (w * h)) {
        throw string("Can't parse level file") + path;
    }
    _tiles = std::make_unique<Tile[]>(w * h);
    _width = w; // set static class vars
    _height = h;
    std::copy(temp_tiles.begin(), temp_tiles.end(), &_tiles[0]);
    cout << "Level " << path << " Loaded. " << w << "x" << h << std::endl;
    buildSprites();
}

void LevelSystem::buildSprites(bool optimise) {
    _sprites.clear();
    _mapTex.clear();
    _mapTex.create(_width * _tileSize, _height * _tileSize);
    struct tp { // tile properties
        sf::Vector2f p;
        sf::Vector2f s;
        sf::Color c;
    };
    vector<tp> tps;
    const auto tls = Vector2f(_tileSize, _tileSize);
    for (size_t y = 0; y < _height; ++y) {
        for (size_t x = 0; x < _width; ++x) {
            Tile t = getTile({ x, y });
            if (t == EMPTY) {
                continue;
            }
            tps.push_back({ getTilePosition({x, y}), tls, getColor(t) });
        }
    }

    const auto nonempty = tps.size();

    // If tile of the same type are next to each other,
    // We can use one large sprite instead of two.
    if (optimise && nonempty) {

        vector<tp> tpo;
        tp last = tps[0];
        size_t samecount = 0;

        for (size_t i = 1; i < nonempty; ++i) {
            // Is this tile compressible with the last?
            bool same = ((tps[i].p.y == last.p.y) &&
                (tps[i].p.x == last.p.x + (tls.x * (1 + samecount))) &&
                (tps[i].c == last.c));
            if (same) {
                ++samecount; // Yes, keep going
                // tps[i].c = Color::Green;
            }
            else {
                if (samecount) {
                    last.s.x = (1 + samecount) * tls.x; // Expand tile
                }
                // write tile to list
                tpo.push_back(last);
                samecount = 0;
                last = tps[i];
            }
        }
        // catch the last tile
        if (samecount) {
            last.s.x = (1 + samecount) * tls.x;
            tpo.push_back(last);
        }

        // No scan down Y, using different algo now that compressible blocks may
        // not be contiguous
        const auto xsave = tpo.size();
        samecount = 0;
        vector<tp> tpox;
        for (size_t i = 0; i < tpo.size(); ++i) {
            last = tpo[i];
            for (size_t j = i + 1; j < tpo.size(); ++j) {
                bool same = ((tpo[j].p.x == last.p.x) && (tpo[j].s == last.s) &&
                    (tpo[j].p.y == last.p.y + (tls.y * (1 + samecount))) &&
                    (tpo[j].c == last.c));
                if (same) {
                    ++samecount;
                    tpo.erase(tpo.begin() + j);
                    --j;
                }
            }
            if (samecount) {
                last.s.y = (1 + samecount) * tls.y; // Expand tile
            }
            // write tile to list
            tpox.push_back(last);
            samecount = 0;
        }

        tps.swap(tpox);
    }

    for (auto& t : tps) {
        auto s = make_unique<sf::RectangleShape>();
        s->setPosition(t.p);
        s->setSize(t.s);
        s->setFillColor(Color::Red);
        s->setFillColor(t.c);
        // s->setFillColor(Color(rand()%255,rand()%255,rand()%255));
        _sprites.push_back(move(s));
    }

    cout << "Level with " << (_width * _height) << " Tiles, With " << nonempty
        << " Not Empty, using: " << _sprites.size() << " Sprites\n";
}

void LevelSystem::render(RenderWindow& window) {
    for (auto& t : _sprites) {
        _mapTex.draw(*t);
    }
    _mapTex.display();
    _mapSprite.setTexture(_mapTex.getTexture());
    window.draw(_mapSprite);
    /*for (auto& t : _sprites) {
        window.draw(*t);
    }*/
    
}

LevelSystem::Tile LevelSystem::getTile(sf::Vector2ul p) {
    if (p.x > _width || p.y > _height) {
        throw string("Tile out of range: ") + to_string(p.x) + "," +
            to_string(p.y) + ")";
    }
    return _tiles[(p.y * _width) + p.x];
}

size_t LevelSystem::getWidth() { return _width; }

size_t LevelSystem::getHeight() { return _height; }

sf::Vector2f LevelSystem::getTilePosition(sf::Vector2ul p) {
    return (Vector2f(p.x, p.y) * _tileSize) + _offset + getMapPosition();
}

std::vector<sf::Vector2ul> LevelSystem::findTiles(LevelSystem::Tile type) {
    auto v = vector<sf::Vector2ul>();
    for (size_t i = 0; i < _width * _height; ++i) {
        if (_tiles[i] == type) {
            v.push_back({ i % _width, i / _width });
        }
    }

    return v;
}

LevelSystem::Tile LevelSystem::getTileAt(Vector2f v) {
    auto a = v - _offset - getMapPosition();
    if (a.x < 0 || a.y < 0) {
        throw string("Tile out of range ");
    }
    return getTile(Vector2ul((v - _offset - getMapPosition()) / (_tileSize)));
}

bool LevelSystem::isOnGrid(sf::Vector2f v) {
    auto a = v - _offset;
    if (a.x < 0 || a.y < 0) {
        return false;
    }
    auto p = Vector2ul((v - _offset) / (_tileSize));
    if (p.x > _width || p.y > _height) {
        return false;
    }
    return true;
}

void LevelSystem::setOffset(const Vector2f& _offset) {
    LevelSystem::_offset = _offset;
    buildSprites();
}

void LevelSystem::unload() {
    cout << "LevelSystem unloading\n";
    _sprites.clear();
    _tiles.reset();
    _width = 0;
    _height = 0;
    _offset = { 0, 0 };
}

const Vector2f& LevelSystem::getOffset() { return _offset; }

float LevelSystem::getTileSize() { return _tileSize; }

void LevelSystem::updateMap() {
#if DEBUG
    sf::Vector2f old_pos = _mapSprite.getPosition();
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        old_pos.x -= 1.f;
        _mapMovement.x -= 1.f;
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        old_pos.x += 1.f;
        _mapMovement.x += 1.f;
    }
    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        old_pos.y -= 1.f;
        _mapMovement.y -= 1.f;
    }
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        old_pos.y += 1.f;
        _mapMovement.y += 1.f;
    }
    _mapSprite.setPosition(old_pos);
#endif // DEBUG
}

void LevelSystem::setMapPosition(sf::Vector2f newpos) {
    _mapSprite.setPosition(newpos);
}

sf::Vector2f LevelSystem::getMapPosition() {
    return _mapSprite.getPosition();
}

void LevelSystem::setMapRotation(sf::Angle newrot) {
    _mapSprite.setRotation(newrot);
}

sf::Angle LevelSystem::getMapRotation() {
    return _mapSprite.getRotation();
}

sf::Vector2f LevelSystem::getMapMovement() {
    return _mapMovement;
}
