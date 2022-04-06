#include <iostream>
#include <thread>
#include "LevelSystem.h"
#include "scene_MainMenu.h"
#include "../lib_ecm/components/cmp_text.h"
#include "../game.h"
#include "engine.h"

using namespace std;
using namespace sf;

void MainMenu::Load() {
	tag = 0;

	auto txt = makeEntity();
	txt->addTag("MenuText"); 
	txt->setPosition(Vector2f(Engine::getWindowSize().x * 0.3, Engine::getWindowSize().y * 0.3));
	//txt->setPosition(Vector2f(50.0f, 50.0f)); 
	auto t = txt->addComponent<TextComponent>("Neighbourhood Nash:\n\nPress 1 for game\nPress 2 for settings\nPress 3 for credits");
	setLoaded(true);
	
}

void MainMenu::UnLoad() {
	Scene::UnLoad(); 
}

void MainMenu::Render() {
	Scene::Render();
}

void MainMenu::Update(const double& dt) {
	if (sf::Keyboard::isKeyPressed(Keyboard::Num1)) {
		Engine::ChangeScene(&L1);
	}
	if (sf::Keyboard::isKeyPressed(Keyboard::Num2)) {
		Engine::ChangeScene(&settings);
	}
	if (sf::Keyboard::isKeyPressed(Keyboard::Num3)) {
		Engine::ChangeScene(&credits);
		//Engine::ChangeScene(&gameover);
		//Engine::ChangeScene(&celebration);
	}
	Scene::Update(dt);
}