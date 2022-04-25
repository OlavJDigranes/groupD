#include <iostream>
#include <thread>
#include "LevelSystem.h"
#include "scene_Settings.h"
#include "../lib_ecm/components/cmp_text.h"
#include "../game.h"

using namespace std;
using namespace sf;

void Settings::Load() {
	tag = -1; 

	//ESC text message
	auto esc = makeEntity();
	esc->setPosition(Vector2f(5, 5));
	auto t = esc->addComponent<ESCTextComponent>("Press ESC to return to menu");

	auto info = makeEntity(); 
	info->setPosition(Vector2f(Engine::getWindowSize().x * 0.3, Engine::getWindowSize().y * 0.2));
	auto i = info->addComponent<TextComponent>("CONTROLS:"); 

	setLoaded(true);
}

void Settings::UnLoad() {
	Scene::UnLoad();
}

void Settings::Update(const double& dt) {
	Scene::Update(dt);
}

void Settings::Render() {
	Scene::Render();
}