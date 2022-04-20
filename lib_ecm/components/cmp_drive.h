#pragma once

#include "../lib_ecm/ecm.h"
#include "Box2D/Dynamics/b2Body.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include <maths.h>

#define DEBUG_TELEPORT

class PlayerDrivingComponent : public Component {
protected:
	Entity* _parent;
	b2Body* _body;
	float _currentSpeed;
	b2Vec2 _size;
	b2Vec2 _halfSize;
	b2Vec2 _direction;
	bodyUserData* _data;

public:
	void Drive(float speed, double dt);
	void Brake(double dt);
	void Rotate(float degrees, float dt);

	void render() override {};
	void update(double dt) override;

	explicit PlayerDrivingComponent(Entity* parent, sf::Vector2f size);
	PlayerDrivingComponent() = delete;
	~PlayerDrivingComponent();
#ifdef DEBUG_TELEPORT
	void teleport(sf::Vector2f pos);
#endif
};