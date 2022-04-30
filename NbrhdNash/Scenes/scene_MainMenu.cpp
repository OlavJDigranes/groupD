#include <iostream>
#include <thread>
#include "LevelSystem.h"
#include "scene_MainMenu.h"
#include "scene_Settings.h"
#include "../lib_ecm/components/cmp_text.h"
#include "../game.h"
#include "engine.h"
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

void MainMenu::Load() {
	tag = 0;

	auto esc = makeEntity();
	esc->setPosition(Vector2f(5, 5));
	if (Joystick::isConnected(0)) {
		auto y = esc->addComponent<ESCTextComponent>("Press Start to exit the game");
	}
	else {
		auto y = esc->addComponent<ESCTextComponent>("Press ESC to exit the game");
	}

	auto txt = makeEntity();
	txt->addTag("MenuText"); 
	txt->setPosition(Vector2f(Engine::getWindowSize().x * 0.3, Engine::getWindowSize().y * 0.25));
	if (Joystick::isConnected(0)) {
		auto t = txt->addComponent<TextComponent>("Neighbourhood Nash:\n\nPress A for game\nPress B for settings\nPress X for scoreboard\nPress Y for credits");
	}
	else {
		auto t = txt->addComponent<TextComponent>("Neighbourhood Nash:\n\nPress 1 for game\nPress 2 for settings\nPress 3 for scoreboard\nPress 4 for credits");
	}
	
	//Game music loop handling. 
	menuLoop.openFromFile("res/music/MainMenuLoop.mp3");
	menuLoop.setLoop(true);
	menuLoop.setVolume(70);
	menuLoop.play();

	//Handling Vsync settings once the game is loaded. 
	settings.ingestFile(); 
	if (settings.vsyncSetting == "V") {
		Engine::setVsync(true); 
	}
	if (settings.vsyncSetting == "B") {
		Engine::setVsync(false); 
	}

	setLoaded(true);
}

void MainMenu::UnLoad() {
	Scene::UnLoad(); 
}

void MainMenu::Render() {
	Scene::Render();
}

void MainMenu::Update(const double& dt) {
	if (sf::Keyboard::isKeyPressed(Keyboard::Num1)) {
		Engine::ChangeScene(&L1);
		menuLoop.setVolume(60); 
	}
	if (sf::Keyboard::isKeyPressed(Keyboard::Num2)) {
		Engine::ChangeScene(&settings);
	}
	if (sf::Keyboard::isKeyPressed(Keyboard::Num3)) {
		Engine::ChangeScene(&scoreboard);
	}
	if (sf::Keyboard::isKeyPressed(Keyboard::Num4)) {
		Engine::ChangeScene(&credits); 
	}

	if (Joystick::isConnected(0)) {
		if (sf::Joystick::isButtonPressed(0, 0)) {
			Engine::ChangeScene(&L1);
			menuLoop.setVolume(60);
		}
		if (sf::Joystick::isButtonPressed(0, 1)) {
			Engine::ChangeScene(&settings);
		}
		if (sf::Joystick::isButtonPressed(0, 2)) {
			Engine::ChangeScene(&scoreboard);
		}
		if (sf::Joystick::isButtonPressed(0, 3)) {
			Engine::ChangeScene(&credits);
		}
	}

	Scene::Update(dt);
}