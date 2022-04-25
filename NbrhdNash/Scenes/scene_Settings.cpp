#include <iostream>
#include <thread>
#include "LevelSystem.h"
#include "scene_Settings.h"
#include "../lib_ecm/components/cmp_text.h"
#include "../game.h"
#include "SFML/Window.hpp"
#include "SFML/Window/Joystick.hpp"

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
		auto i = info->addComponent<TextComponent>("CONTROLS:\nRT for acceleration\nLT for braking\nLeft Joystick for turning");
	}
	else {
		auto i = info->addComponent<TextComponent>("CONTROLS:\nW for acceleration\nS for braking\nA for turning left\nD for turning right");
	}

	auto info2 = makeEntity(); 
	info2->setPosition(Vector2f(Engine::getWindowSize().x * 0.5, Engine::getWindowSize().y * 0.2));
	if (Joystick::isConnected(0)) {
		auto i2 = info2->addComponent<TextComponent>("SELECT RESOLUTION:\nA: 1280 x 720\nB: 1920 x 1080\nX: 2560 x 1440");
	}
	else {
		auto i2 = info2->addComponent<TextComponent>("SELECT RESOLUTION:\nQ: 1280 x 720\nW: 1920 x 1080\nE: 2560 x 1440");
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
		Settings::UnLoad();
		Settings::Load(); 
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		resTag = 2;
		Settings::UnLoad();
		Settings::Load();
	}
	if (Keyboard::isKeyPressed(Keyboard::E)) {
		resTag = 3;
		Settings::UnLoad();
		Settings::Load();
	}	
}

void Settings::Render() {
	Scene::Render();
}