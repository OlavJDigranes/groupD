#pragma once

#include "LevelSystem.h"
#include "engine.h"
#include "components/cmp_sprite.h"

//Credits scene class
class Credits : public Scene {
public:
	Credits() = default;
	~Credits() = default; 

	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;
};