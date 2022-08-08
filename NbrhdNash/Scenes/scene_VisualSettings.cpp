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
#include "scene_VisualSettings.h"

using namespace std;
using namespace sf;

void VisualSettings::Load() {
	tag = -8;

	sf::Joystick::Identification joystickID = sf::Joystick::getIdentification(0);

	auto esc = makeEntity();
	esc->setPosition(Vector2f(5, 5));
	if (Joystick::isConnected(0)) {
		auto y = esc->addComponent<ESCTextComponent>("Press Start to return to the menu\nPress A to select a menu option");
	}
	else {
		auto y = esc->addComponent<ESCTextComponent>("Press ESC to return to the menu\nPress Enter to select a menu option");
	}


	auto titleText = makeEntity();
	titleText->setPosition(Vector2f(Engine::getWindowSize().x * 0.2, Engine::getWindowSize().y * 0.25));
	auto u = titleText->addComponent<TextComponent>("Visual Settings");
	float txtOffset = 0.0f;

	setLoaded(true);
}

void VisualSettings::UnLoad() {
	Scene::UnLoad();
}

void VisualSettings::Update(const double& dt) {
	if (Keyboard::isKeyPressed(Keyboard::Escape) && btnTimer3 <= 0.0f) {
		Engine::ChangeScene(&settings); 
	}

	btnTimer3 -= dt;
	Scene::Update(dt);
}

void VisualSettings::Render() {
	Scene::Render();
}