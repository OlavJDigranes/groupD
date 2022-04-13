#pragma once

#include "LevelSystem.h"
#include "engine.h"
#include "components/cmp_sprite.h"

class Settings : public Scene {
public:
	Settings() = default; 
	~Settings() = default; 

	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;
};