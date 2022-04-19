#include <iostream>
#include <thread>
#include "LevelSystem.h"
#include "scene_MainMenu.h"
#include "../lib_ecm/components/cmp_text.h"
#include "../game.h"
#include "engine.h"
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

void MainMenu::Load() {
	tag = 0;

	auto esc = makeEntity();
	esc->setPosition(Vector2f(5, 5));
	auto y = esc->addComponent<ESCTextComponent>("Press ESC to exit the game");
	setLoaded(true);

	auto txt = makeEntity();
	txt->addTag("MenuText"); 
	txt->setPosition(Vector2f(Engine::getWindowSize().x * 0.3, Engine::getWindowSize().y * 0.25));
	auto t = txt->addComponent<TextComponent>("Neighbourhood Nash:\n\nPress 1 for game\nPress 2 for settings\nPress 3 for scoreboard\nPress 4 for credits");
	setLoaded(true);
	
	menuLoop.openFromFile("res/music/MainMenuLoop.mp3");
	menuLoop.setLoop(true);
	menuLoop.setVolume(70);
	menuLoop.play();
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
		//Engine::ChangeScene(&steering); 
		//mainMenuLoop.stop(); 
	}
	if (sf::Keyboard::isKeyPressed(Keyboard::Num2)) {
		Engine::ChangeScene(&settings);
	}
	if (sf::Keyboard::isKeyPressed(Keyboard::Num3)) {
		Engine::ChangeScene(&scoreboard);
		//Engine::ChangeScene(&gameover);
		//Engine::ChangeScene(&celebration);
	}
	if (sf::Keyboard::isKeyPressed(Keyboard::Num4)) {
		Engine::ChangeScene(&credits); 
	}
	Scene::Update(dt);
}