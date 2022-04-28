//"steering.h"
#pragma once

#include "engine.h"

//TESTING CLASS

class SteeringScene : public Scene {
public:
	void Load() override;
	void UnLoad() override;
	void Update(const double& dt) override;
	void Render() override;
};