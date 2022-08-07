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

class ControlSettings : public Settings {
protected:
	float btnTime5 = 1.0f;
public:
	ControlSettings() = default; 
	~ControlSettings() = default; 

	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;
};