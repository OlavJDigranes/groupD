#include "scene_Scoreboard.h"
#include <iostream>
#include <fstream>
#include "SFML/Window.hpp"
#include "SFML/Window/Joystick.hpp"

using namespace std;
using namespace sf; 

void Scoreboard::Load() {
	
	tag = -5;

	int counter = 0;
	vector<string> lines;
	std::string line;
	vector<shared_ptr<Entity>> scoreboardText;
	ifstream timeFile;

	//Removing underscores for readability
	timeFile.open("times.txt", std::ios_base::in);
	if (timeFile.is_open()) {
		while (!timeFile.eof()) {
			line.resize(timeFile.tellg());
			timeFile >> line;
			lines.push_back(line);
			counter++;

			//Make a vector of 5 text elements.
			if (counter == 1) {
				auto txt1 = makeEntity();
				scoreboardText.push_back(txt1);
			}
			if (counter == 2) {
				auto txt2 = makeEntity();
				scoreboardText.push_back(txt2);
			}
			if (counter == 3) {
				auto txt3 = makeEntity();
				scoreboardText.push_back(txt3);
			}
			if (counter == 4) {
				auto txt4 = makeEntity();
				scoreboardText.push_back(txt4);
			}
			if (counter == 5) {
				auto txt5 = makeEntity();
				scoreboardText.push_back(txt5);
			}
		}
	}

	//Removing underscores for readability
	for (int i = 0; i < lines.size(); i++) {
		for (int j = 0; j < lines[i].length(); j++) {
			if (lines[i][j] == '_') {
				lines[i][j] = ' ';
			}
		}
	}

	sf::Joystick::Identification joystickID = sf::Joystick::getIdentification(0);

	auto esc = makeEntity();
	esc->setPosition(Vector2f(5, 5));
	if (Joystick::isConnected(0)) {
		auto y = esc->addComponent<ESCTextComponent>("Press Start to exit the game");
	}
	else {
		auto y = esc->addComponent<ESCTextComponent>("Press ESC to exit the game");
	}

	//Populate the elements if needed, and place on screen. 
	for (int i = 0; i < counter; i++) {
		int dist = i * 35;
		std::cout << dist << endl; 
		scoreboardText[i]->setPosition(Vector2f(Engine::getWindowSize().x * 0.3, (Engine::getWindowSize().y * 0.2) + dist));
		auto s = scoreboardText[i]->addComponent<TextComponent>(std::to_string(i + 1) + ": " + lines[i] + "\n");
	}
	timeFile.close();
	setLoaded(true);

}

void Scoreboard::UnLoad() {
	Scene::UnLoad();
}

void Scoreboard::Update(const double& dt) {
	Scene::Update(dt);
}

void Scoreboard::Render() {
	Scene::Render();
}