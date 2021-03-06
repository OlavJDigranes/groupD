#include <iostream>
#include <thread>
#include "LevelSystem.h"
#include "scene_Settings.h"
#include "scene_MainMenu.h"
#include "../lib_ecm/components/cmp_text.h"
#include "../game.h"
#include "SFML/Window.hpp"
#include "SFML/Window/Joystick.hpp"
#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;
using namespace sf;

void Settings::Load() {
	tag = -1;

	sf::Joystick::Identification joystickID = sf::Joystick::getIdentification(0);
	
	auto esc = makeEntity();
	esc->setPosition(Vector2f(5, 5));
	if (Joystick::isConnected(0)) {
		auto y = esc->addComponent<ESCTextComponent>("Press Start to exit the game");
	}
	else {
		auto y = esc->addComponent<ESCTextComponent>("Press ESC to exit the game");
	}

	auto info = makeEntity();
	info->setPosition(Vector2f(Engine::getWindowSize().x * 0.3, Engine::getWindowSize().y * 0.2));
	if (Joystick::isConnected(0)) {
		auto i = info->addComponent<TextComponent>("CONTROLS:\nRT for acceleration\nLT for braking\nLeft Joystick for turning\n\nPress BACK to save settings");
	}
	else {
		auto i = info->addComponent<TextComponent>("CONTROLS:\nW for acceleration\nS for braking\nA for turning left\nD for turning rightz\n\nPress X to save settings");
	}

	auto info2 = makeEntity(); 
	info2->setPosition(Vector2f(Engine::getWindowSize().x * 0.5, Engine::getWindowSize().y * 0.2));
	if (Joystick::isConnected(0)) {
		auto i2 = info2->addComponent<TextComponent>("SELECT RESOLUTION:\nA: 1280 x 720\nY: 1920 x 1080\nX: 2560 x 1440\n\nV-SYNC:\nLB: On\nRB: Off");
	}
	else {
		auto i2 = info2->addComponent<TextComponent>("SELECT RESOLUTION:\nQ: 1280 x 720\nW: 1920 x 1080\nE: 2560 x 1440\n\nV-SYNC:\nV: On\nB: Off");
	}
	

	setLoaded(true);
}

void Settings::UnLoad() {
	Scene::UnLoad(); 
}

void Settings::Update(const double& dt) {
	Scene::Update(dt);
	if (Keyboard::isKeyPressed(Keyboard::Q)) {
		resTag = 1;
		imageSetting = "Q "; 
		Settings::UnLoad();
		Settings::Load(); 
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		resTag = 2;
		imageSetting = "W ";
		Settings::UnLoad();
		Settings::Load();
	}
	if (Keyboard::isKeyPressed(Keyboard::E)) {
		resTag = 3;
		imageSetting = "E ";
		Settings::UnLoad();
		Settings::Load();
	}
	if (Keyboard::isKeyPressed(Keyboard::V)) {
		Engine::setVsync(true);
		vsyncSetting = "V ";
	}
	if (Keyboard::isKeyPressed(Keyboard::B)) {
		Engine::setVsync(false); 
		vsyncSetting = "B ";
	}
	if (Keyboard::isKeyPressed(Keyboard::X)) {
		saveSettings();
	}

	if (Joystick::isConnected(0)) {
		if (sf::Joystick::isButtonPressed(0, 0)) {
			resTag = 1;
			imageSetting = "Q ";
			Settings::UnLoad();
			Settings::Load();
		}
		if (sf::Joystick::isButtonPressed(0, 3)) {
			resTag = 2;
			imageSetting = "W ";
			Settings::UnLoad();
			Settings::Load();
		}
		if (sf::Joystick::isButtonPressed(0, 2)) {
			resTag = 3;
			imageSetting = "E ";
			Settings::UnLoad();
			Settings::Load();
		}
		if (sf::Joystick::isButtonPressed(0, 4)) {
			Engine::setVsync(true);
			vsyncSetting = "V ";
		}
		if (sf::Joystick::isButtonPressed(0, 5)) {
			Engine::setVsync(false);
			vsyncSetting = "B ";
		}
		if (sf::Joystick::isButtonPressed(0, 7)) {
			saveSettings(); 
		}
	}
}

void Settings::Render() {
	Scene::Render();
}

void Settings::saveSettings() {
	settingsFile.open("settings.txt", std::ios_base::out);
	settingsFile << imageSetting;
	settingsFile << vsyncSetting;
	settingsFile.close();
}

//Helper function for ingesting file if it exists
void Settings::ingestFile() {
	std::string line;
	ifstream settingsFileIn;
	settingsFileIn.open("settings.txt", std::ios_base::in);

	//checking if file is empty
	if (settingsFileIn.is_open()) {
		while (!settingsFileIn.eof()) {
			line.resize(settingsFileIn.tellg());
			settingsFileIn >> line;
			lines.push_back(line);
			counter++;
		}
	}

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
}