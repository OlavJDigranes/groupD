#include "cmp_drive.h"


PlayerDrivingComponent::PlayerDrivingComponent(Entity* parent, const sf::Vector2f size) : Component(parent) {
	_parent = parent;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = Physics::sv2_to_bv2(_parent->getPosition());
    _body = Physics::GetWorld()->CreateBody(&bodyDef);

	_body->SetGravityScale(0);
    
	_size = Physics::sv2_to_bv2(size, true);
    
    _currentSpeed = 0;
    _body->SetActive(true);
    _direction = b2Vec2(0, -1);
    _body->SetLinearDamping(0.5);
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
    if (_body->GetAngle() > 4 * atan(1)) {
        _body->SetTransform(_body->GetPosition(), -4 * atan(1));
    }
    _body->SetTransform(_body->GetPosition(), _body->GetAngle() + sf::deg2rad(degrees * dt));
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