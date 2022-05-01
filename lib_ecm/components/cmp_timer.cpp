#include "cmp_timer.h"
#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;
using namespace sf; 

//TODO: Ask why file reading is not working. 
//Starts the level timer for the given level. 
LevelTimer::LevelTimer(Entity* const p, int levelTag) : Component(p) {
	tempLevelTag = levelTag; 
	timer.restart(); 
	timeInSeconds = 0;
}

//Stops the level timer and outputs the time to a txt file 
void LevelTimer::LevelTimerStop() {
	
	ingestFile();

	timeInSeconds = LevelTimer::timer.getElapsedTime().asSeconds();
	timeFile.open("times.txt", std::ios_base::out);

	//Local variables
	std::string outputLine;
	vector<float> times; 

	outputLine = CreateTimeFileString(timeInSeconds);
	

	//if file is empty or has less than 5 lines add new line. 
	if (timeFile.is_open()) {
		/*
		if (counter < 5) {
			timeFile << outputLine;

			//Only runs the for loop if there was sometihng in the file
			if (counter > 0) {
				for (int i = 0; i < counter; i++) {
					timeFile << lines[i] + " ";
				}
			}

		}
		*/ 
		//if file is has 5 lines Compare the times of current and existing lines and keep the 5 highest times. 
		if (counter > 0) {
			//PSEUDOCODE:
				//make a vecotr of floats. use int a = 3; float b = (float)a;
				//make the minute andd second substrings into int and float. std::stof() - convert string to float.
				//compare the new time in seconds (floats) to old times (floats) in seconds and discard the slowest one. Keep only 5 fastest, and save them to file. 
			float tempOldTimeInSeconds;
			float tempOldMinutes;
			float tempOldSeconds;
			string tempSubStringSecs;
			string tempSubStringMins;

			times.push_back(timeInSeconds);

			for (int i = 0; i < counter; i++) {
				tempOldTimeInSeconds = 0.0f;
				tempOldMinutes = 0.0f;
				tempOldSeconds = 0.0f;
				tempSubStringMins = " ";
				tempSubStringSecs = " ";

				if (lines[i].length() > 22) {
					tempSubStringMins = lines[i].substr(9, 2);
					tempOldMinutes = std::stof(tempSubStringMins);

					tempSubStringSecs = lines[i].substr(25, 7);
					tempOldSeconds = std::stof(tempSubStringSecs);
					tempOldTimeInSeconds = (tempOldMinutes * 60) + tempOldSeconds;
					times.push_back(tempOldTimeInSeconds);
				}
				else {
					tempSubStringSecs = lines[i].substr(9, 7);
					tempOldTimeInSeconds = std::stof(tempSubStringSecs);
					times.push_back(tempOldTimeInSeconds);
				}
			}

			sort(times.begin(), times.end());

			for (int i = 1; i < times.size(); i++) {
				if (times[i] == times [i-1]) {
					times.erase(times.begin() + (i-1)); 
				}
			}

			for (int i = 0; i < times.size(); i++) {
				timeFile << CreateTimeFileString(times[i]);
			}
		}
		else {
			timeFile << outputLine;
		}
	}
	
	timeInSeconds = 0; 
	timeFile.close();
}

//Helper function for writing to the file. 
string LevelTimer::CreateTimeFileString(float time) {
	//New Time handling.
	int timeMins = 0;
	float timeSecs = 0.0f;
	std::string newLine;

	while (time > 0) {
		if (time >= 60) {
			timeMins += 1;
			time -= 60;
		}
		else {
			timeSecs = time;
			time -= time;
		}
	}

	//TODO roundTime still outputs 4 zeros which chould not be there. 
	if (timeMins == 0) {
		newLine = "Level_" + std::to_string(tempLevelTag) + ":_" + std::to_string(LevelTimer::roundTime(timeSecs)) + "_seconds! ";
	}
	if (timeMins > 0) {
		newLine = "Level_" + std::to_string(tempLevelTag) + ":_" + std::to_string(timeMins) + "_minute(s)_and_" + std::to_string(LevelTimer::roundTime(timeSecs)) + "_seconds! ";
	}
	return newLine; 
}

//Helper function for proper rounding of the times. https://www.geeksforgeeks.org/rounding-floating-point-number-two-decimal-places-c-c/
float LevelTimer::roundTime(float f) {
	float value = (int)(f * 100 + .5);
	return (float)value / 100;
}

//Helper function for ingesting file if it exists
void LevelTimer::ingestFile() {
	std::string line;
	ifstream timeFileIn;
	timeFileIn.open("times.txt", std::ios_base::in);

	//checking if file is empty
	if (timeFileIn.peek() != std::ifstream::traits_type::eof()) {
		while (!timeFileIn.eof()) {
			line.resize(timeFileIn.tellg());
			timeFileIn >> line;
			if (line != "EOF") {
				lines.push_back(line);
				counter++;
			}
		}
	}
}