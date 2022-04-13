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
	auto t = esc->addComponent<ESCTextComponent>("Press ESC to return to menu");

	auto info = makeEntity();
	info->setPosition(Vector2f(Engine::getWindowSize().x * 0.3, Engine::getWindowSize().y * 0.3));
	//auto y = info->addComponent<TextComponent>("CONGRATULATIONS!");
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