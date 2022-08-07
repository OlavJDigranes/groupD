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

class AudioSettings : public Settings {
protected:
	float btnTimer4 = 1.0f;
public:
	AudioSettings() = default;
	~AudioSettings() = default;

	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;

	/*
	//Volume Ranges
	float minVolume = 0.0f;
	float maxVolume = 100.0f;
	float maxvolumeMod = 2.0f;

	//Volume variables
	float menuLoopVolume = 70;

	//Volume modifiers, start at one
	float sfxVolumeMod = 1.0f;
	float ambienceVolumeMod = 1.0f;
	*/
};