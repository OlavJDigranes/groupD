#include "cmp_actor_movement.h"
#include <LevelSystem.h>
#include <engine.h>
#include <iostream>
using namespace sf;
using namespace std;

void ActorMovementComponent::update(double dt) {}

ActorMovementComponent::ActorMovementComponent(Entity* p)
    : _speed(100.0f), Component(p) {}

//THIS MAY NEED REDOING dependent on testing. 
bool ActorMovementComponent::validMove(const sf::Vector2f& pos) {
  return (LevelSystem::getTileAt(pos) != LevelSystem::EDGEWALL || 
      LevelSystem::getTileAt(pos) != LevelSystem::SHOPS ||
      LevelSystem::getTileAt(pos) != LevelSystem::EMPTY ||
      LevelSystem::getTileAt(pos) != LevelSystem::BIRDSPAWN ||
      LevelSystem::getTileAt(pos) != LevelSystem::TREE ||
      LevelSystem::getTileAt(pos) != LevelSystem::NEIGHBOURHOUSE ||
      LevelSystem::getTileAt(pos) != LevelSystem::EMPTYHOUSE);
  // return true;
}

void ActorMovementComponent::move(const sf::Vector2f& p) {
  auto pp = _parent->getPosition() + p;
  if (validMove(pp)) {
    _parent->setPosition(pp);
  }
}

void ActorMovementComponent::move(float x, float y) {
  move(Vector2f(x, y));
}
