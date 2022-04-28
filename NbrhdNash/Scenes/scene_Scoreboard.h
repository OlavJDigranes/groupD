#pragma once

#include "LevelSystem.h"
#include "engine.h"
#include "components/components.h"

//Scoreboard scene class
class Scoreboard : public Scene {
protected:
public:
	Scoreboard() = default;
	~Scoreboard() = default; 
	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;
};