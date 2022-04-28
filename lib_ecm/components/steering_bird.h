#pragma once

#include "../lib_ecm/ecm.h"
#include "../NbrhdNash/steering.h"
#include "Box2D/Dynamics/b2Body.h"
#include "system_physics.h"
#include <maths.h>

class BirdFlyToTarget : public SteeringBehaviour {
private:
    Entity* _entity;
    Entity* _entityTarget;
    sf::Vector2f _target;
    bool _focusEntity;
    float _maxSpeed;
public:
    BirdFlyToTarget() = delete;
    BirdFlyToTarget(Entity* character, Entity* entityTarget, sf::Vector2f targetLoc, float maxSpeed, bool focusOnEntity) : _entity(character), _target(targetLoc), _maxSpeed(maxSpeed), _focusEntity(focusOnEntity), _entityTarget(entityTarget) { }
    void setTarget(sf::Vector2f* target) { _target = *target; _focusEntity = false; }
    void setEntityTarget(Entity* target) { _entityTarget = target; _focusEntity = true; }
    SteeringOutput getSteering() const noexcept;
};