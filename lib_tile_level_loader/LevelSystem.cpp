#include "LevelSystem.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace sf;

std::unique_ptr<LevelSystem::TILE[]> LevelSystem::_tiles;
size_t LevelSystem::_width;
size_t LevelSystem::_height;
Vector2f LevelSystem::_offset(0.0f, 0.0f);

float LevelSystem::_tileSize(100.f);
vector<std::unique_ptr<sf::RectangleShape>> LevelSystem::_sprites;
std::shared_ptr<Vector2f> LevelSystem::_startPos;
std::shared_ptr<Vector2f> LevelSystem::_endPos;

std::map<LevelSystem::TILE, sf::Color> LevelSystem::_colours{ {WALL, Color::White}, {END, Color::Red}, {START, Color::Blue} };

sf::Color LevelSystem::getColor(LevelSystem::TILE t) {
    auto it = _colours.find(t);
    if (it == _colours.end()) {
        _colours[t] = Color::Transparent;
    }
    return _colours[t];
}

void LevelSystem::setColor(LevelSystem::TILE t, sf::Color c) {
    auto it = _colours.find(t);
    if (it != _colours.end())
    {
        it->second = c;
    }
}

LevelSystem::TILE LevelSystem::getTile(Vector2ul p) {
    if (p.x > _width || p.y > _height) {
        throw string("Tile out of range: ") + to_string(p.x) + "," + to_string(p.y) + ")";
    }
    return _tiles[(p.y * _width) + p.x];
}

LevelSystem::TILE LevelSystem::getTileAt(Vector2f loc) {
    size_t ecks = floor(loc.x) / _tileSize;
    size_t ouaie = floor(loc.y) / _tileSize;
    return getTile({ ecks, ouaie });
}

std::vector<sf::Vector2ul> LevelSystem::findTiles(LevelSystem::TILE Tile) {
    std::vector<sf::Vector2ul> list;
    for (size_t x = 0; x < _width; x++) {
        for (size_t y = 0; y < _height; y++) {
            auto tile = getTile({ x, y });
            if (tile == Tile) {
                list.push_back({ x, y });
            }
        }
    }
    return list;
}

Vector2f LevelSystem::getTilePosition(Vector2ul p) {
    return (Vector2f(p.x, p.y) * _tileSize);
}

Vector2f LevelSystem::getStartTilePosition() {
    return *_startPos;
}

Vector2f LevelSystem::getEndTilePosition() {
    return *_endPos;
}

void LevelSystem::loadLevelFile(const std::string& path, float tileSize) {
    _tileSize = tileSize;
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

    std::vector<TILE> temp_tiles;
    for (int i = 0; i < buffer.size(); ++i) {
        const char c = buffer[i];
        switch (c) {
        case 'w':
            temp_tiles.push_back(WALL);
            break;
        case 's':
            temp_tiles.push_back(START);
            break;
        case 'e':
            temp_tiles.push_back(END);
            break;
        case ' ':
            temp_tiles.push_back(EMPTY);
            break;
        case '+':
            temp_tiles.push_back(WAYPOINT);
            break;
        case 'n':
            temp_tiles.push_back(ENEMY);
            break;
        case '\n':      // end of line
            if (w == 0) { // if we haven't written width yet
                w = i;      // set width
            }
            h++; // increment height
            break;
        default:
            cout << c << endl; // Don't know what this tile type is
        }
    }
    if (temp_tiles.size() != (w * h)) {
        throw string("Can't parse level file") + path;
    }
    _tiles = std::make_unique<TILE[]>(w * h);
    _width = w; //set static class vars
    _height = h;
    std::copy(temp_tiles.begin(), temp_tiles.end(), &_tiles[0]);
    cout << "Level " << path << " Loaded. " << w << "x" << h << std::endl;
    buildSprites();
}

void LevelSystem::buildSprites() {
    _sprites.clear();
    for (size_t y = 0; y < LevelSystem::getHeight(); ++y) {
        for (size_t x = 0; x < LevelSystem::getWidth(); ++x) {
            auto s = make_unique<RectangleShape>();
            s->setPosition(getTilePosition({ x, y }));
            s->setSize(Vector2f(_tileSize, _tileSize));
            s->setFillColor(getColor(getTile({ x, y })));
            _sprites.push_back(move(s));
            if (getTile({ x, y }) == TILE::START) {
                _startPos = make_shared<Vector2f>(getTilePosition({ x, y }));
            }
            if (getTile({ x, y }) == TILE::END) {
                _endPos = make_shared<Vector2f>(getTilePosition({ x, y }));
            }
        }
    }
}

void LevelSystem::Render(RenderWindow& window) {
    for (size_t i = 0; i < _width * _height; ++i) {
        window.draw(*_sprites[i]);
    }
}