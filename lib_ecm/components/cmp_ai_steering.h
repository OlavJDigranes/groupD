//"cmp_ai_steering.h"
#pragma once
#include <../lib_ecm/ecm.h>
#include "../NbrhdNash/steering.h"
#include "steering_bird.h"
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
    sf::Vector2i _mapBounds;
    bool _isActive;
    bool _atTarget;
    bool validMove(const sf::Vector2f&) const;
public:
    void SetActive(bool Active);
    bool IsActive();
    bool HasArrived() { return _atTarget; }
    void update(double) override;
    void move(const sf::Vector2f&, float f);
    void move(float x, float y, float f);
    void rotate(SteeringOutput rot, float dt);
    void render() override { }
    explicit SteeringComponent(Entity* p, Entity* player, bool ActiveOnCreation, sf::Vector2i mapBounds);
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

class BirdSteering : public SteeringComponent {
protected:
    BirdFlyToTarget fly;
    sf::Vector2f _target;
    Entity* _entityTarget;
    bool _targetingEntity;
public:
    BirdSteering() = delete;
    explicit BirdSteering(Entity* p, Entity* player, bool ActiveOnCreation, sf::Vector2i mapBounds);
    void SetTargetLocation(const sf::Vector2f* target) { _target = *target; fly.setTarget(&_target); _targetingEntity = false; };
    void SetEntityAsTarget(Entity* target_entity) { _entityTarget = target_entity; fly.setEntityTarget(target_entity); _targetingEntity = true;  }
    sf::Vector2f GetTargetLocation() { return _target; };
    bool IsTargetingEntity() { return _targetingEntity; }
    void rotate(SteeringOutput rot, float dt);
    void update(double) override;
    ~BirdSteering();
};