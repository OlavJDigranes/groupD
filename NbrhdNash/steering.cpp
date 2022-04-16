//"steering.cpp"
#include "steering.h"

using namespace sf;

SteeringOutput Seek::getSteering() const noexcept {
    SteeringOutput steering;
    steering.direction = _target->getPosition() - _character->getPosition();
    steering.direction = normalize(steering.direction);
    steering.direction *= _maxSpeed;
    steering.rotation = 0.0f;
    return steering;
}

SteeringOutput Flee::getSteering() const noexcept {
    SteeringOutput steering;
    steering.direction = _character->getPosition() - _target->getPosition();
    steering.direction = normalize(steering.direction);
    steering.direction *= _maxSpeed;
    steering.rotation = 0.0f;
    return steering;
}

SteeringOutput Face::getSteering() const noexcept {
    SteeringOutput steering;
    float tan = 0.0f;
    steering.direction = _target->getPosition() - _character->getPosition();
    steering.direction = normalize(steering.direction);
    tan = atan2(steering.direction.y, steering.direction.x);
    steering.rotation = (sf::rad2deg(tan));
    steering.direction *= _maxSpeed;
    std::cout << steering.rotation << std::endl; 
    return steering;
}