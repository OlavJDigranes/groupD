#include <iostream>
#include <thread>
#include "LevelSystem.h"
#include "scene_Celebration.h"
#include "../lib_ecm/components/cmp_text.h"
#include "../game.h"

using namespace std;
using namespace sf;

void Celebration::Load() {
	tag = -4;

	auto esc = makeEntity();
	esc->setPosition(Vector2f(5, 5));
	auto t = esc->addComponent<TextComponent>("Press ESC to return to menu");

	auto info = makeEntity();
	info->setPosition(Vector2f(Engine::getWindowSize().x * 0.3, Engine::getWindowSize().y * 0.3));
	auto y = info->addComponent<TextComponent>("CONGRATULATIONS!");
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