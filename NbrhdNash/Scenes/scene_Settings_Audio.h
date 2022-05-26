#pragma once

#include "LevelSystem.h"
#include "engine.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include "components/components.h"
#include <thread>
#include "../game.h"
#include "SFML/Window.hpp"
#include "SFML/Window/Joystick.hpp"
#include "scene_Settings.h"

using namespace std;
using namespace sf;

class SettingsAudio : public Scene {
public:
protected:
	SettingsAudio() = default;
	~SettingsAudio() = default;

	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;
};