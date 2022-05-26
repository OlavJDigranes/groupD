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
protected:
	int selectedOption3; 

	std::vector<std::shared_ptr<Entity>> settingsOptions;
	std::vector<std::shared_ptr<TextComponent>> settingsTexts;

	std::vector<std::shared_ptr<Entity>> audioOptions;
	std::vector<std::shared_ptr<TextComponent>> audioTexts;
	float btnTimer4 = 1.0f;
public:
	SettingsAudio() = default;
	~SettingsAudio() = default;

	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;

	//Min volume
	float minVolume = 0.0f;

	//Max volume
	float maxVolume = 100.0f;
	float maxvolumeMod = 2.0f;

	float menuLoopVolume = 70;

	//modifiers start at 1. 
	float sfxVolumeMod = 1.0f;
	float ambienceVolumeMod = 1.0f;
};