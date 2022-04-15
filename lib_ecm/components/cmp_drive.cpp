#include "cmp_drive.h"


PlayerDrivingComponent::PlayerDrivingComponent(Entity* parent, const sf::Vector2f size) : Component(parent) {
	_parent = parent;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = Physics::sv2_to_bv2(_parent->getPosition());
    _body = Physics::GetWorld()->CreateBody(&bodyDef);

	_body->SetGravityScale(0);
    
	_size = Physics::sv2_to_bv2(size, true);
    
	//_body->SetSleepingAllowed(false);
	//_body->SetFixedRotation(true);
    _currentSpeed = 0;
    _body->SetActive(true);
    _direction = b2Vec2(0, -1);
    _body->SetLinearDamping(0.5);
}

void PlayerDrivingComponent::Drive(float speed, double dt) {
    while (_currentSpeed <= 20 && _currentSpeed >= 0) {
        //_body->ApplyForceToCenter(speed * dt * _direction, true);
        _body->SetLinearVelocity(b2Vec2(speed * dt * _direction));
        auto debug = speed * dt * _direction;
        printf("debug = %f, %f\n", debug.x, debug.y);
        _currentSpeed += speed * dt;
    }
}

void PlayerDrivingComponent::Rotate(float degrees, float dt) {
    auto _arc = ((_direction.x * 1) /* + (_direction.y * 0)*/) / sqrt((pow(_direction.x, 2) + pow(_direction.y, 2)) * (1 + 0));
    auto angle = (_direction.y / abs(_direction.y)) * acos(_arc);
    auto rot_x = sqrt(pow(_direction.x, 2) + pow(_direction.y, 2)) * cos(angle + degrees * dt);
    auto rot_y = sqrt(pow(_direction.x, 2) + pow(_direction.y, 2)) * sin(angle + degrees * dt);
    _direction = b2Vec2(rot_x, rot_y);
    //printf("direction: %f, %f\n", _direction.x, _direction.y);
    printf("rotation: %f\n", _body->GetAngle() + sf::deg2rad(degrees));
    if (_body->GetAngle() > 4 * atan(1)) {
        _body->SetTransform(_body->GetPosition(), -4 * atan(1));
    }
    _body->SetTransform(_body->GetPosition(), _body->GetAngle() + sf::deg2rad(degrees));
    _parent->setRotation(_parent->getRotation() + (degrees * dt));
}

void PlayerDrivingComponent::update(double dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        Rotate(-2, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        Rotate(2, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        Drive(200, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        Drive(-200, dt);
    }
    _body->SetLinearVelocity(_body->GetLinearVelocity().Length() * _direction);
    _currentSpeed = _body->GetLinearVelocity().Length();
    _parent->setPosition(Physics::bv2_to_sv2(_body->GetPosition()));
}