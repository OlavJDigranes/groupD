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
        if (*_index < _path->size()) {
            // Could do this in a single line - expanded for clarity
            float new_x = ls::getOffset().x + _path->at(*_index).x * ls::getTileSize();
            float new_y = ls::getOffset().y + _path->at(*_index).y * ls::getTileSize();
            //_parent->setPosition(Vector2f(new_x, new_y));
            //++_index;
            if (_parent->getPosition().x >= new_x && _parent->getPosition().x <= new_x + ls::getTileSize() &&
                _parent->getPosition().y >= new_y && _parent->getPosition().y <= new_y + ls::getTileSize()) {
                ++*_index;

                //printf("AI Pathfinding Index: %u\n", *_index);
                //printf("New target: %f, %f\n", new_x, new_y);
                //printf("Parent position: %f, %f\n", _parent->getPosition().x, _parent->getPosition().y);
            }
            /*if (_parent->getPosition() == sf::Vector2f(new_x, new_y)) {
                ++_index;
            }*/
        }
    }
    if (*_index == _path->size()) {
        std::lock_guard<std::mutex> lck(_hasPath_mtx);
        // Are we already loading asynchronously?
        if (_hasPath_future.valid() // yes
            &&                     // Has it finished?
            _hasPath_future.wait_for(std::chrono::seconds(0)) ==
            std::future_status::ready) {
            // Yes
            //_hasPath_future.get();
            FindNewCheckpoint_async();
            _hasPath = true;
        }
        //FindNewCheckpoint();
    }
}

PathfindingComponent::PathfindingComponent(Entity* p) : Component(p) {
    _path = std::make_shared<std::vector<sf::Vector2i>>();
    _index = std::make_shared<size_t>(0);
}

void PathfindingComponent::setPath(std::vector<sf::Vector2i>& path) {
    *_index = 0;
    *_path = path;
    float new_x = ls::getOffset().x + _path->at(*_index).x * ls::getTileSize();
    float new_y = ls::getOffset().y + _path->at(*_index).y * ls::getTileSize();
    //printf("AI Pathfinding Index: %u\n", *_index);
    //printf("New target: %f, %f\n", new_x, new_y);
    //printf("Parent position: %f, %f\n", _parent->getPosition().x, _parent->getPosition().y);
}

void PathfindingComponent::FindNewCheckpoint() {
    Vector2ul cur = { (size_t)(_parent->getPosition().x / ls::getTileSize()), (size_t)(_parent->getPosition().y / ls::getTileSize()) };
    auto currentTile = ls::getTileAt(_parent->getPosition());
    srand(time(NULL));
    auto newTileVal = rand() % 4 + 50;
    if (newTileVal != currentTile) {
        auto newChkPt = ls::findTiles(newTileVal).at(0);
        Vector2i loc = Vector2i((int)newChkPt.x, (int)newChkPt.y);
        Vector2i init = Vector2i(cur.x, cur.y);
        auto path = pathFind(init, loc);
        setPath(path);
    }
}

void PathfindingComponent::FindNewCheckpoint_async() {
    std::lock_guard<std::mutex> lck(_hasPath_mtx);
    std::async(&PathfindingComponent::FindNewCheckpoint, this);
}

PathfindingComponent::~PathfindingComponent() {
    _path = nullptr;
    _index = nullptr;
    Component::~Component();
}