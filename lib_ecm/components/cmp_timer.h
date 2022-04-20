#pragma once

#include <../lib_ecm/ecm.h>
#include "engine.h"
#include <fstream>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace sf; 

class LevelTimer : public Component {
protected:
	//Timer
	sf::Clock timer; 
	int tempLevelTag; 
	float timeInSeconds; 
	fstream timeFile; 
public: 
	LevelTimer() = delete;

	explicit LevelTimer(Entity* const p, int levelTag);

	~LevelTimer() = default;
	void LevelTimerStop();
	string WriteToTimeFile(float time); 
	float roundTime(float f); 

	void update(double dt) override {};
	void render() override {};
};