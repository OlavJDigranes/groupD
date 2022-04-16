//"cmp_ai_steering.h"
#pragma once
#include <../lib_ecm/ecm.h>
#include "../NbrhdNash/steering.h"
#include "Box2D/Dynamics/b2Body.h"
#include "system_physics.h"
#include <maths.h>

class SteeringComponent : public Component {
protected:
    Seek _seek;
    Flee _flee;
    Face _face;
    Entity* _player;
    b2Body* _body;
    b2Vec2 _size;
    b2Vec2 _direction;
    float32 _rotation;
    bool validMove(const sf::Vector2f&) const;
public:
    void update(double) override;
    void move(const sf::Vector2f&, float f);
    void move(float x, float y, float f);
    void rotate(SteeringOutput rot, float dt);
    void render() override { }
    explicit SteeringComponent(Entity* p, Entity* player);
    SteeringComponent() = delete;
};

/*
class SteeringComponent : public Component {
protected:
    Seek _seek;
    Flee _flee;
    Entity* _player;
    bool validMove(const sf::Vector2f&) const;
public:
    void update(double) override;
    void move(const sf::Vector2f&);
    void move(float x, float y);
    void render() override { }
    explicit SteeringComponent(Entity* p, Entity* player);
    SteeringComponent() = delete;
};

*/