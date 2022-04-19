#include "cmp_timer.h"


using namespace std;
using namespace sf; 

//Starts the level timer for the given level. 
LevelTimer::LevelTimer(Entity* const p, int levelTag) : Component(p) {
	tempLevelTag = levelTag; 
	timer.restart(); 
	timeInSeconds = 0;
}

//Stops the level timer and outputs the time to a txt file 
void LevelTimer::LevelTimerStop() {
	timeInSeconds = timer.getElapsedTime().asSeconds(); 
	timeFile.open("times.txt", std::ios_base::app); 

	int timeMins = 0;
	float timeSecs = 0.0f; 

	while (timeInSeconds > 0) {
		if (timeInSeconds >= 60) {
			timeMins += 1; 
			timeInSeconds -= 60; 
		}
		else {
			timeSecs = timeInSeconds; 
			timeInSeconds -= timeInSeconds; 
		}
	}

	if(timeMins == 0){
		//timeFile << "Level %d: %f seconds!", tempLevelTag, timeSecs;
		timeFile << "Level " << std::to_string(tempLevelTag) << ": " << std::to_string(timeSecs) << " seconds!";
	}
	if (timeMins > 0) {
		//timeFile << "Level %d: %d minutes, %f seconds!", tempLevelTag, timeMins, timeSecs;
		timeFile << "Level " << std::to_string(tempLevelTag) << ": " << std::to_string(timeMins) << " minutes and" << std::to_string(timeSecs) << " seconds!";
	}

	timeInSeconds = 0; 
	timeFile.close();
}