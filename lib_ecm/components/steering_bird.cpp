#include "steering_bird.h"

SteeringOutput BirdFlyToTarget::getSteering() const noexcept {
	SteeringOutput steering;
	float tan = 0.0f;
	if (_focusEntity && _entityTarget != nullptr) {
		steering.direction = _entityTarget->getPosition() - _entity->getPosition();
	}
	else {
		steering.direction = _target - _entity->getPosition();
	}
	steering.direction = normalize(steering.direction);
	steering.direction *= _maxSpeed;
	tan = atan2(steering.direction.y, steering.direction.x);
	steering.rotation = tan * 180 / (4 *  atan(1));
	return steering;
}