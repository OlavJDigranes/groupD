#pragma once

#include "LevelSystem.h"
#include "engine.h"
#include "components/cmp_sprite.h"

class Celebration : public Scene {
public:
	Celebration () = default;
	~Celebration() = default;

	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;
};