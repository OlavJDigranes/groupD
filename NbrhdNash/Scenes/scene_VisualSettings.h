#pragma once

#include "scene_Settings.h"
#include "LevelSystem.h"
#include "engine.h"
#include "components/cmp_sprite.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include "components/components.h"

using namespace std;
using namespace sf;

class VisualSettings : public Settings {
protected:
	float btnTimer3 = 1.0f;
public:
	VisualSettings() = default;
	~VisualSettings() = default;

	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;
};