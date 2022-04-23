#pragma once

#include "../lib_ecm/ecm.h"
#include "cmp_drive.h"

class PlayerController : public Component {
protected:
	std::weak_ptr<DrivingComponent> _driver;

public:
	void update(double) override;
	void render() override {};
	explicit PlayerController(Entity* p, std::weak_ptr<DrivingComponent> drive_cmp);
	~PlayerController();
};