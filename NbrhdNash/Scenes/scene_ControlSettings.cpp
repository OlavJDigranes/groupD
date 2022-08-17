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
#include "scene_ControlSettings.h"

using namespace std;
using namespace sf;

void ControlSettings::Load() {
	tag = -7;

	sf::Joystick::Identification joystickID = sf::Joystick::getIdentification(0);

	auto esc = makeEntity();
	esc->setPosition(Vector2f(5, 5));
	if (Joystick::isConnected(0)) {
		auto y = esc->addComponent<ESCTextComponent>("Press Start to return to the menu\n");
	}
	else {
		auto y = esc->addComponent<ESCTextComponent>("Press ESC to return to the menu\n");
	}

	auto titleText = makeEntity();
	titleText->setPosition(Vector2f(Engine::getWindowSize().x * 0.2, Engine::getWindowSize().y * 0.25));
	auto u = titleText->addComponent<TextComponent>("Controls");
	float txtOffset = 0.0f;

	auto info = makeEntity();
	info->setPosition(Vector2f(Engine::getWindowSize().x * 0.3, Engine::getWindowSize().y * 0.2));
	if (Joystick::isConnected(0)) {
		auto i = info->addComponent<TextComponent>("\nRT for acceleration\nLT for braking\nLeft Joystick for turning\n\n");
	}
	else {
		auto i = info->addComponent<TextComponent>("\nW for acceleration\nS for braking\nA for turning left\nD for turning right\n\n");
	}


	setLoaded(true);
}

void ControlSettings::UnLoad() {
	Scene::UnLoad();
}

void ControlSettings::Update(const double& dt) {
	if (Keyboard::isKeyPressed(Keyboard::Escape) && btnTimer3 <= 0.0f) {
		Engine::ChangeScene(&settings);
	}

	btnTimer3 -= dt;
	Scene::Update(dt);
}

void ControlSettings::Render() {
	Scene::Render();
}