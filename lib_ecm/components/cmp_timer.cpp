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

	vector<string> lines;
	std::string line;
	std::string newLine;
	int counter = 0;

	//checking if file is empty
	if (timeFile.peek() == std::ifstream::traits_type::eof()) {
		while (!timeFile.eof()) {
			timeFile >> line;
			lines.push_back(line);
			counter++;
		}
	}

	//New Time handling.
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

	if (timeMins == 0) {
		newLine = "Level " + std::to_string(tempLevelTag) + ": " + std::to_string(timeSecs) + " seconds!";
	}
	if (timeMins > 0) {
		newLine = "Level " + std::to_string(tempLevelTag) + ": " + std::to_string(timeMins) + " minutes and" + std::to_string(timeSecs) + " seconds!";
	}

	//if file is empty or has less than 5 lines add new line. 
	if(counter < 5){
		timeFile << newLine; 
	}
	//if file is has 5 lines Compare the times of current and existing lines and keep the 5 highest times. 
	if (counter >= 5) {
		//PSEUDOCODE:
			//make a vecotr of floats. use int a = 3; float b = (float)a;
			//make the minute andd second substrings into int and float. std::stof() - convert string to float.
			//compare the new time in seconds (floats) to old times (floats) in seconds and discard the slowest one. Keep only 5 fastest, and save them to file. 
	}

	timeInSeconds = 0; 
	timeFile.close();
}