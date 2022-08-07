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
#include "scene_AudioSettings.h"

using namespace std;
using namespace sf;

void AudioSettings::Load() {
	tag = -6;

	sf::Joystick::Identification joystickID = sf::Joystick::getIdentification(0);

	auto esc = makeEntity();
	esc->setPosition(Vector2f(5, 5));
	if (Joystick::isConnected(0)) {
		auto y = esc->addComponent<ESCTextComponent>("Press Start to exit the game\nPress A to select a menu option");
	}
	else {
		auto y = esc->addComponent<ESCTextComponent>("Press ESC to return to the menu\nPress Enter to select a menu option");
	}

	setLoaded(true);
}

void AudioSettings::UnLoad() {

}

void AudioSettings::Update(const double& dt) {

}

void AudioSettings::Render() {

}