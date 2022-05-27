#pragma once

using namespace std; 

struct audioVol {
	//Volume Ranges
	float minVolume = 0.0f;
	float maxVolume = 100.0f;
	float maxvolumeMod = 2.0f;

	//Volume variables
	float menuLoopVolume = 70;

	//Volume modifiers, start at one
	float sfxVolumeMod = 1.0f;
	float ambienceVolumeMod = 1.0f;
};