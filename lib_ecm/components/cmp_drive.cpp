#include "cmp_drive.h"


PlayerDrivingComponent::PlayerDrivingComponent(Entity* parent, const sf::Vector2f size) : Component(parent) {
	_parent = parent;
    _direction = b2Vec2(0, -1);
    _currentSpeed = 0;
    _size = Physics::sv2_to_bv2(size, true);
    _halfSize = Physics::sv2_to_bv2(0.5f * size);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = Physics::sv2_to_bv2(_parent->getPosition());
    _body = Physics::GetWorld()->CreateBody(&bodyDef);
	_body->SetGravityScale(0);
    _body->SetTransform(_body->GetPosition(), sf::deg2rad(_parent->getRotation()));
    _body->SetActive(true);
    _body->SetLinearDamping(0.5);

    b2FixtureDef fixDef;
    b2PolygonShape box;
    box.SetAsBox(_size.x, size.y, Physics::sv2_to_bv2(_parent->getPosition()), (float32)0);
    fixDef.shape = &box;
    fixDef.density = 0.35;
}

void PlayerDrivingComponent::Drive(float speed, double dt) {
    if (_body->GetLinearDamping() > 0.5) {
        _body->SetLinearDamping(0.5);
    }
    if (_currentSpeed <= 4 && _currentSpeed >= 0) {
        _body->SetLinearVelocity(b2Vec2((_currentSpeed + (speed * dt)) * _direction));
    }
}

void PlayerDrivingComponent::Brake(float dt) {
    if (_currentSpeed > 0) {
        _body->SetLinearDamping(2);
    }
}

void PlayerDrivingComponent::Rotate(float degrees, float dt) {
    _direction = Physics::sv2_to_bv2(Physics::bv2_to_sv2(_direction).rotatedBy(sf::degrees(degrees * dt)));
    auto forceLoc = _body->GetWorldPoint(b2Vec2(_direction));
    _body->ApplyForce(Physics::sv2_to_bv2(Physics::bv2_to_sv2(_direction).rotatedBy(sf::degrees(degrees * dt))), forceLoc, true);
    _parent->setRotation(_parent->getRotation() + (degrees * dt));
}

void PlayerDrivingComponent::update(double dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        Rotate(-180, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        Rotate(180, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        Drive(1, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        Brake(dt);
    }
    if (_currentSpeed == 0) {
        _body->SetLinearDamping(0.5);
    }
    _body->SetLinearVelocity(_body->GetLinearVelocity().Length() * _direction);
    _currentSpeed = _body->GetLinearVelocity().Length();
    _parent->setPosition(Physics::bv2_to_sv2(_body->GetPosition()));
}