#pragma once

#include <../lib_ecm/ecm.h>
#include "engine.h"
#include <fstream>

using namespace std;
using namespace sf; 

class LevelTimer : public Component {
protected:
	//Timer
	sf::Clock timer; 
	int tempLevelTag; 
	float timeInSeconds; 
	ofstream timeFile; 
public: 
	LevelTimer() = delete;

	explicit LevelTimer(Entity* const p, int levelTag);

	~LevelTimer() = default;
	void LevelTimerStop();
	void update(double dt) override {};
	void render() override {};
};