#include <iostream>
#include <thread>
#include "LevelSystem.h"
#include "scene_Celebration.h"
#include "scene_Level1.h"
#include "../lib_ecm/components/cmp_text.h"
#include "../game.h"

using namespace std;
using namespace sf;

void Celebration::Load() {
	tag = -4;

	L1.cityAtmos.stop();

	sf::Joystick::Identification joystickID = sf::Joystick::getIdentification(0);

	auto esc = makeEntity();
	esc->setPosition(Vector2f(5, 5));
	if (Joystick::isConnected(0)) {
		auto y = esc->addComponent<ESCTextComponent>("Press Start to exit the game");
	}
	else {
		auto y = esc->addComponent<ESCTextComponent>("Press ESC to exit the game");
	}

	//Multicolour CONGRATULATIONS text. 
	auto info = makeEntity();
	info->setPosition(Vector2f(Engine::getWindowSize().x * 0.3, Engine::getWindowSize().y * 0.3));
	auto g = info->addComponent<GreenTextComponent>("C    A       N  ");
	auto r = info->addComponent<RedTextComponent>("  N     L       ");
	auto b = info->addComponent<BlueTextComponent>(" O  R           !");
    auto y = info->addComponent<YellowTextComponent>("   G T        S ");
    auto m = info->addComponent<MagentaTextComponent>("       U  T O   ");
	auto c = info->addComponent<CyanTextComponent>("         A  I    ");
	setLoaded(true);
}

void Celebration::UnLoad() {
	Scene::UnLoad();
}

void Celebration::Update(const double& dt) {
	Scene::Update(dt);
}

void Celebration::Render() {
	Scene::Render();
}