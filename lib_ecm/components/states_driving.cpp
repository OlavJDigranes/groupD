#include "states_driving.h"

void AcceleratingState::execute(Entity* p, double dt) noexcept {
	auto AI = p->get_components<AIDrivingComponent>();
	auto driver = AI[0]->getDriver();
	driver->Drive(1, dt);
}

void BrakingState::execute(Entity* p, double dt) noexcept {
	//_driver->Brake(dt);
	auto AI = p->get_components<AIDrivingComponent>();
	auto driver = AI[0]->getDriver();
	driver->Drive(1, dt);
}

void TurningLeftState::execute(Entity* p, double dt) noexcept {
	auto AI = p->get_components<AIDrivingComponent>();
	auto driver = AI[0]->getDriver();
	driver->Rotate((-2 - 1 / *_angle) * *_angle, dt);
	driver->Drive(0.5, dt);

}

void TurningRightState::execute(Entity* p, double dt) noexcept {
	auto AI = p->get_components<AIDrivingComponent>();
	auto driver = AI[0]->getDriver();
	driver->Rotate((2 + 1 / *_angle) * *_angle, dt);
	driver->Drive(0.5, dt);
}