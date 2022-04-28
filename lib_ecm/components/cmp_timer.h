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
	ofstream timeFile; 
	vector<string> lines;
	int counter = 0;
public: 
	LevelTimer() = delete;

	explicit LevelTimer(Entity* const p, int levelTag);

	~LevelTimer() = default;
	void LevelTimerStop();
	string CreateTimeFileString(float time); 
	float roundTime(float f); 
	void ingestFile();

	void update(double dt) override {};
	void render() override {};
};