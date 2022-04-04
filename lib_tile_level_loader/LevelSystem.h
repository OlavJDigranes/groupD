#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include "../lib_maths/maths.h"

#define ls LevelSystem

class LevelSystem {
public:
    static void loadLevelFile(const std::string&, float tileSize = 50.0f);
    static void unload();
    static void render(sf::RenderWindow& window);

    typedef unsigned char Tile;

    //Tile enumeration using legend from shared document
    enum TILES {
        EMPTY = ' ',
        EDGEWALL = 'w',
        HOME = 'h',
        CHECKPOINT = 'k',
        SHOPS = 's', 
        ROAD = 'r', 
        BIRDSPAWN = 'b',
        CAR1SPAWN = 'c',
        CAR2SPAWN = 'd',
        CAR3SPAWN = 'e',
        TREE = 't', 
        GRASS = 'g',
        GRATEROAD = 'a', 
        NEIGHBOURHOUSE = 'n', 
        EMPTYHOUSE = 'm', 
        PARKINGSPACE = 'p',
        AICHECKPOINT1 = '1',
        AICHECKPOINT2 = '2',
        AICHECKPOINT3 = '3',
        AICHECKPOINT4 = '4',
        AICHECKPOINT5 = '5'

    };

    static Tile getTile(sf::Vector2ul);

    static Tile getTileAt(sf::Vector2f);

    static bool isOnGrid(sf::Vector2f);

    static size_t getWidth();

    static size_t getHeight();

    static sf::Vector2f getTilePosition(sf::Vector2ul);

    static std::vector<sf::Vector2ul> findTiles(Tile);

    static sf::Color getColor(Tile t);

    static void setColor(Tile t, sf::Color c);

    static void setOffset(const sf::Vector2f& _offset);

    static const sf::Vector2f& getOffset();

    static float getTileSize();

    static void updateMap();

    static void setMapPosition(sf::Vector2f newpos);

    static sf::Vector2f getMapPosition();

    static void setMapRotation(sf::Angle);

    static sf::Angle getMapRotation();

protected:
    static std::unique_ptr<Tile[]> _tiles;
    static size_t _width;
    static size_t _height;
    static sf::Vector2f _offset;

    static std::vector<std::unique_ptr<sf::RectangleShape>> _sprites;

    static void buildSprites(bool optimise = true);

    static float _tileSize; // for rendering
    static std::map<Tile, sf::Color> _colours;
    
    static sf::RenderTexture _mapTex; // render texture to output map and AI display to
    static sf::Sprite _mapSprite; // sprite for map texture to render to

private:
    LevelSystem() = delete;

    ~LevelSystem() = delete;
};

