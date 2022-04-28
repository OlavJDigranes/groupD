#include <iostream>
#include <thread>
#include "LevelSystem.h"
#include "scene_GameOver.h"
#include "../lib_ecm/components/cmp_text.h"
#include "../game.h"
#include "SFML/Window.hpp"
#include "SFML/Window/Joystick.hpp"

using namespace std;
using namespace sf;


void GameOver::Load() {
	tag = -3;

	sf::Joystick::Identification joystickID = sf::Joystick::getIdentification(0);

	auto esc = makeEntity();
	esc->setPosition(Vector2f(5, 5));
	if (Joystick::isConnected(0)) {
		auto y = esc->addComponent<ESCTextComponent>("Press Start to exit the game");
	}
	else {
		auto y = esc->addComponent<ESCTextComponent>("Press ESC to exit the game");
	}

	auto txt = makeEntity();
	txt->addTag("GameOverText");
	txt->setPosition(Vector2f(Engine::getWindowSize().x * 0.3, Engine::getWindowSize().y * 0.3));
	auto y = txt->addComponent<RedTextComponent>("GAME OVER");

	//Game over sound
	gameOverBuffer.loadFromFile("res/music/GameOver.mp3");
	gameOverSound.setBuffer(gameOverBuffer);
	gameOverSound.setVolume(80);
	gameOverSound.play();

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