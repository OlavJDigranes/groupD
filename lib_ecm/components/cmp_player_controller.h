#pragma once

#include "../lib_ecm/ecm.h"
#include "cmp_drive.h"
#include "SFML/Window.hpp"
#include "SFML/Window/Joystick.hpp"

class PlayerController : public Component {
protected:
	std::weak_ptr<DrivingComponent> _driver;

public:
	void update(double) override;
	void render() override {};
	explicit PlayerController(Entity* p, std::weak_ptr<DrivingComponent> drive_cmp);
	~PlayerController();
};