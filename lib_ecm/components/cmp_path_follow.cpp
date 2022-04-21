//"cmp_path_follow.cpp"
#include "cmp_path_follow.h"
#include "../NbrhdNash/astar.h"
#include <../lib_tile_level_loader/LevelSystem.h>

using namespace sf;
using namespace std;

void PathfindingComponent::update(double dt) {
    _elapsed += dt;
    if (_elapsed >= 0.1) {
        _elapsed = 0.0;
        if (_index < _path.size()) {
            // Could do this in a single line - expanded for clarity
            float new_x = ls::getOffset().x + _path[_index].x * ls::getTileSize();
            float new_y = ls::getOffset().y + _path[_index].y * ls::getTileSize();
            _parent->setPosition(Vector2f(new_x, new_y));
            ++_index;
        }
    }
    if (_index == _path.size()) {
        FindNewCheckpoint();
    }
}

PathfindingComponent::PathfindingComponent(Entity* p) : Component(p) {}

void PathfindingComponent::setPath(std::vector<sf::Vector2i>& path) {
    _index = 0;
    _path = path;
}

void PathfindingComponent::FindNewCheckpoint() {
    Vector2ul cur = { (size_t)(_parent->getPosition().x / ls::getTileSize()), (size_t)(_parent->getPosition().y / ls::getTileSize()) };
    auto currentTile = ls::getTileAt(_parent->getPosition());
    srand(time(NULL));
    auto newTileVal = rand() % 4 + 50;
    if (newTileVal != currentTile) {
        auto newChkPt = ls::findTiles(newTileVal).at(0);
        std::vector<sf::Vector2i> _newPath;
        Vector2i loc = Vector2i((int)newChkPt.x, (int)newChkPt.y);
        Vector2i init = Vector2i(cur.x, cur.y);
        auto path = pathFind(init, loc);
        setPath(path);
    }
}