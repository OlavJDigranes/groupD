#include <iostream>
#include <thread>
#include "LevelSystem.h"
#include "scene_MainMenu.h"
#include "../lib_ecm/components/cmp_text.h"
#include "../game.h"

using namespace std;
using namespace sf;

void Settings::Load() {
	tag = -1; 

	auto esc = makeEntity();
	esc->setPosition(Vector2f(5, 5));
	auto t = esc->addComponent<TextComponent>("Press ESC to return to menu");
	setLoaded(true);
}

void Settings::UnLoad() {
	Scene::UnLoad();
}

void Settings::Update(const double& dt) {
	//if (sf::Keyboard::isKeyPressed(Keyboard::Escape)) {
	//	Engine::ChangeScene(&menu);
	//}
	Scene::Update(dt);
}

void Settings::Render() {
	Scene::Render();
}