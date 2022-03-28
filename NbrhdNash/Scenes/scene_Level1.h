#pragma once

#include "LevelSystem.h"
#include "engine.h"

class Level1 : public Scene {
public:
	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;
};