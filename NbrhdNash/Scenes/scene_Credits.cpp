#include <iostream>
#include <thread>
#include "LevelSystem.h"
#include "scene_Credits.h"
#include "../lib_ecm/components/cmp_text.h"
#include "../game.h"

using namespace std;
using namespace sf;

void Credits::Load() {
	tag = -2; 

	auto esc = makeEntity(); 
	esc->setPosition(Vector2f(5, 5));
	auto t = esc->addComponent<ESCTextComponent>("Press ESC to return to menu");

	auto info = makeEntity();
	info->setPosition(Vector2f(Engine::getWindowSize().x * 0.3, Engine::getWindowSize().y * 0.3));
	auto y = info->addComponent<TextComponent>("Game Programming:\nRory Gatens\nOlav J. Digranes\n\nSound Design:\nNicholas Di Biase");
	setLoaded(true);
}

void Credits::UnLoad(){
	Scene::UnLoad();
}

void Credits::Update(const double& dt) {
	Scene::Update(dt);
}

void Credits::Render() {
	Scene::Render();
}
