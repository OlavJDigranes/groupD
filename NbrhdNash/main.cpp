#include <SFML/Graphics.hpp>
#include "LevelSystem.h"
#include "engine.h"
#include "Scenes/scene_Level1.h"
#include "game.h"
#include "Scenes/scene_Settings.h"

std::unique_ptr<sf::RenderWindow> window;
const int gameWidth = 1920; // change to file read values
const int gameHeight = 1080;

MainMenu menu; 
Level1 L1;
Credits credits;
Settings settings; 
Celebration celebration;
GameOver gameover; 
SteeringScene steering; 
Scoreboard scoreboard;

int main() {
	//Ingest save state file 
	std::string line;
	ifstream settingsFileIn;
	vector<string> lines;
	int counter = 0;
	settingsFileIn.open("settings.txt", std::ios_base::in);
	string vsyncSetting = " ";
	string imageSetting = " ";
	bool vsyncState = false; 

	//checking if file is empty
	if (settingsFileIn.is_open()) {
		while (!settingsFileIn.eof()) {
			line.resize(settingsFileIn.tellg());
			settingsFileIn >> line;
			lines.push_back(line);
			counter++;
		}
	}

	//Ingesting saved settings, setting image resolution
	if (counter-1 == 1) {
		if (lines[0] == "Q") {
			imageSetting = lines[0];
		}
		if (lines[0] == "W") {
			imageSetting = lines[0];
		}
		if (lines[0] == "E") {
			imageSetting = lines[0];
		}
		if (lines[0] == "V") {
			vsyncSetting = lines[0];
		}
		if (lines[0] == "B") {
			vsyncSetting = lines[0];
		}
	}
	if (counter-1 == 2) {
		imageSetting = lines[0];
		vsyncSetting = lines[1];
	}

	settingsFileIn.close();

	//Starting application with provided settings. 
	if (vsyncSetting == "V") {
		vsyncState = true; 
	}

	if (imageSetting == " " || imageSetting == "W") {
		Engine::Start(gameWidth, gameHeight, "Neighbourhood Nash!", &menu, vsyncState);
	}
	if (imageSetting == "Q") {
		Engine::Start(1280, 720, "Neighbourhood Nash!", &menu, vsyncState);
	}
	if (imageSetting == "E") {
		Engine::Start(2560, 1440, "Neighbourhood Nash!", &menu, vsyncState);
	}	
}