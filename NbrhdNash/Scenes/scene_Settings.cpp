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
		auto y = esc->addComponent<ESCTextComponent>("Press Start to exit the game\nPress A to select a menu option");
	}
	else {
		auto y = esc->addComponent<ESCTextComponent>("Press ESC to return to the menu\nPress Enter to select a menu option");
	}

	constexpr int optionNmb = 4;
	const string options[optionNmb] = { "Audio","Controls","Video","Back" };
	selectedOption2 = 0;

	auto titleText = makeEntity();
	titleText->setPosition(Vector2f(Engine::getWindowSize().x * 0.2, Engine::getWindowSize().y * 0.25));
	auto u = titleText->addComponent<TextComponent>("Settings & Help");
	float txtOffset = 0.0f;
	for (int i = 0; i < optionNmb; i++) {
		settingsOptions.push_back(makeEntity());
		settingsTexts.push_back(settingsOptions[i]->addComponent<TextComponent>(options[i]));
		if (i != 0) {
			settingsTexts[i]->ChangeColor(sf::Color(50, 50, 50, 255));
		}
		txtOffset -= 35.0f;
		settingsOptions[i]->setPosition(Vector2f(Engine::getWindowSize().x * 0.2, (Engine::getWindowSize().y * 0.25) - txtOffset));
	}

	/*
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
	*/

	setLoaded(true);
}

void Settings::UnLoad() {
	Scene::UnLoad(); 
}

void Settings::Update(const double& dt) {

	//Keyboard
	if ((Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) && btnTimer3 <= 0) {
		btnTimer3 = 1.0f;
		if (selectedOption2 - 1 >= 0) {
			settingsTexts[selectedOption2]->ChangeColor(sf::Color(50, 50, 50, 255));
			selectedOption2--;
			settingsTexts[selectedOption2]->ChangeColor(Color::White);
		}
		printf("W");
	}

	if ((Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) && btnTimer3 <= 0) {
		btnTimer3 = 1.0f;
		if (selectedOption2 + 1 < settingsOptions.size()) {
			settingsTexts[selectedOption2]->ChangeColor(sf::Color(50, 50, 50, 255));
			selectedOption2++;
			settingsTexts[selectedOption2]->ChangeColor(Color::White);
		}
		printf("S");
	}

	if (Keyboard::isKeyPressed(Keyboard::Enter) && btnTimer3 <= 0) {
		btnTimer3 = 1.0f;
		settingsOptions.clear();
		settingsTexts.clear();
		switch (selectedOption2) {
		case 0:
			printf("arse\n"); 
			break;
		case 1:
			printf("fuck\n");
			break;
		case 2:
			printf("yeee\n");
			break;
		case 3:
			Engine::ChangeScene(&menu);
			break;
		default:
			break;
		}
		printf("EE");
	}

	btnTimer3 -= dt;

	Scene::Update(dt);
	/*
	* OLD
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
	*/
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