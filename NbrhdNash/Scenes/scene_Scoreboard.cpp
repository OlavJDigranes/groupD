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
	ifstream timeFile; 

	timeFile.open("times.txt");
	if (timeFile.is_open()) {
		while (!timeFile.eof()) {
			timeFile >> line; 
			lines.push_back(line); 
			counter++; 
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

	auto txt = makeEntity();
	txt->setPosition(Vector2f(Engine::getWindowSize().x * 0.3, Engine::getWindowSize().y * 0.2));
	for (int i = 0; i < counter; i++) {
		auto s = txt->addComponent<TextComponent>(std::to_string(i+1) + lines[i] + "\n ");
	}
	timeFile.close(); 
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