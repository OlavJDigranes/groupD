#include "cmp_movement.h"
#include <SFML/Window/Keyboard.hpp>
#include <engine.h>

void BasicMovementComponent::update(double dt) {
    Vector2f direction(0, 0);

    if (Keyboard::isKeyPressed(Keyboard::A)) {
        direction.x -= 1.0f;
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        direction.x += 1.0f;
    }
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        direction.y -= 1.0f;
    }
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        direction.y += 1.0f;
    }
    move(normalize(direction) * _speed * (float)dt);
}

BasicMovementComponent::BasicMovementComponent(Entity* p)
    : _speed(100.0f), Component(p) {}

bool BasicMovementComponent::validMove(Vector2f& pos) {
    if (pos.x < 0.0f || pos.x > Engine::GetWindow().getSize().x ||
        pos.y < 0.0f || pos.y > Engine::GetWindow().getSize().y) {
        return false;
    }
    return true;
}

void BasicMovementComponent::move(const sf::Vector2f& p) {
    auto new_pos = _parent->getPosition() + p;
    if (validMove(new_pos)) {
        _parent->setPosition(new_pos);
    }
}

void BasicMovementComponent::move(float x, float y) {
    move(Vector2f(x, y));
}