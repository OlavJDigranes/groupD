#pragma once
#include "ecm.h"

using namespace std;
using namespace sf;

class BasicMovementComponent : public Component {
protected:
	float _speed;
	bool validMove(Vector2f&);
public:
	void update(double) override;
	void render() override {}
	void move(const Vector2f&);
	void move(float x, float y);
	explicit BasicMovementComponent(Entity* p);
	BasicMovementComponent() = delete;

	void setSpeed(float new_s) { _speed = new_s; }
	float getSpeed() { return _speed; }

};