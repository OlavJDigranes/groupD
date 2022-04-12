#include <iostream>
#include <thread>
#include "LevelSystem.h"
#include "scene_GameOver.h"
#include "../lib_ecm/components/cmp_text.h"
#include "../game.h"

using namespace std;
using namespace sf;


void GameOver::Load() {
	tag = -3;

	auto esc = makeEntity();
	esc->setPosition(Vector2f(5, 5));
	auto t = esc->addComponent<ESCTextComponent>("Press ESC to return to menu");
	setLoaded(true);

	auto txt = makeEntity();
	txt->addTag("GameOverText");
	txt->setPosition(Vector2f(Engine::getWindowSize().x * 0.3, Engine::getWindowSize().y * 0.3));
	auto y = txt->addComponent<TextComponent>("GAME OVER");
	setLoaded(true);
}

void GameOver::UnLoad() {
	Scene::UnLoad();
}

void GameOver::Update(const double& dt) {
	Scene::Update(dt);
}

void GameOver::Render() {
	Scene::Render();
}