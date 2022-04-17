#include "cmp_drive.h"


PlayerDrivingComponent::PlayerDrivingComponent(Entity* parent, const sf::Vector2f size) : Component(parent) {
	_parent = parent;
    _direction = b2Vec2(0, -1);
    _currentSpeed = 0;
    _size = Physics::sv2_to_bv2(size, true);
    _halfSize = Physics::sv2_to_bv2(0.5f * size);

    // Body definition and assignment to parent
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = Physics::sv2_to_bv2(_parent->getPosition());
    _body = Physics::GetWorld()->CreateBody(&bodyDef);
	_body->SetGravityScale(0);
    _body->SetTransform(Physics::sv2_to_bv2(_parent->getPosition()), sf::deg2rad(_parent->getRotation()));
    _body->SetActive(true);
    _body->SetLinearDamping(0.5);
    _body->SetAngularDamping(1);
    _body->SetFixedRotation(false);

    //Fixture definition and assignment to body
    b2FixtureDef fixDef;
    b2PolygonShape box;
    box.SetAsBox(_size.x, _size.y, _body->GetWorldCenter(), _body->GetAngle());
    fixDef.shape = &box;
    fixDef.density = 0.006;
    _body->CreateFixture(&fixDef);
}

void PlayerDrivingComponent::Drive(float speed, double dt) {
    // If brakes have been activated then reset damping
    if (_body->GetLinearDamping() > 0.5) {
        _body->SetLinearDamping(0.5);
    }
    // If below top speed, set body velocity to increase in direction and let parent (sprite) update
    if (_body->GetLinearVelocity().LengthSquared() <= pow(8, 2) && _body->GetLinearVelocity().LengthSquared() >= 0) {
        _body->SetLinearVelocity(b2Vec2((_currentSpeed + (speed * dt)) * _direction));
        _parent->setPosition(Physics::bv2_to_sv2(_body->GetPosition()));
        _currentSpeed += speed * dt;
    }
}

void PlayerDrivingComponent::Brake() {
    // Increase damping if car is moving
    if (_currentSpeed > 0) {
        _body->SetLinearDamping(2);
    }
}

void PlayerDrivingComponent::Rotate(float degrees, float dt) {
    // Rotate parent and update body to match
    _direction = Physics::sv2_to_bv2(Physics::bv2_to_sv2(_direction).rotatedBy(sf::degrees(degrees * dt)));
    auto forceLoc = _body->GetWorldPoint(b2Vec2(_direction));
    _parent->setRotation(_parent->getRotation() + (degrees * dt));
    _body->SetTransform(_body->GetPosition(), sf::deg2rad(_parent->getRotation()));
}

void PlayerDrivingComponent::update(double dt) {
    // Control inputs
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        Rotate(-180, dt);   // Turn left
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        Rotate(180, dt);    // Turn right
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        Drive(1, dt);   // Drive forwards
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        Brake();  // Brake
    }
    if (_currentSpeed == 0) {
        _body->SetLinearDamping(0.5);   // if car is stationary then reduce damping
    }
    _body->SetLinearVelocity(_body->GetLinearVelocity().Length() * _direction); // ensure the car is always travelling forwards when turning with no accel
    _currentSpeed = _body->GetLinearVelocity().Length(); // Update speed to follow damping effects
    _parent->setPosition(Physics::bv2_to_sv2(_body->GetPosition())); // Set parent to follow body when not moving
}