#pragma once

struct {
	//Min volume
	float minVolume = 0.0f;

	//Max volume
	float maxVolume = 100.0f;
	float maxvolumeMod = 2.0f;

	float menuLoopVolume = 70;

	//modifiers start at 1. 
	float sfxVolumeMod = 1.0f;
	float ambienceVolumeMod = 1.0f;
} audioVol;
