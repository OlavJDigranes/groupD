#include <iostream>
#include <thread>
#include "LevelSystem.h"
#include "scene_MainMenu.h"
#include "scene_Settings.h"
#include "scene_Level1.h"
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
	if (Joystick::isConnected(0)) {
		auto y = esc->addComponent<ESCTextComponent>("Press Start to exit the game\nPress A to select a menu option");
	}
	else {
		auto y = esc->addComponent<ESCTextComponent>("Press ESC to exit the game\nPress Enter to select a menu option");
	}

	constexpr int optionNmb = 4; 
	const string options[optionNmb] = { "Start Game","Settings & Help","Scoreboard","Credits" };
	selectedOption = 0; 

	auto titleText = makeEntity(); 
	titleText->setPosition(Vector2f(Engine::getWindowSize().x * 0.3, Engine::getWindowSize().y * 0.25)); 
	auto u = titleText->addComponent<TextComponent>("Neighbourhood Nash"); 
	float txtOffset = 0.0f; 
	for (int i = 0; i < optionNmb; i++) {
		menuOptions.push_back(makeEntity()); 
		menuTexts.push_back(menuOptions[i]->addComponent<TextComponent>(options[i]));
		if (i != 0) {
			menuTexts[i]->ChangeColor(sf::Color(50, 50, 50, 255));
		}
		txtOffset -= 35.0f; 
		menuOptions[i]->setPosition(Vector2f(Engine::getWindowSize().x * 0.3, (Engine::getWindowSize().y * 0.25) - txtOffset)); 
	}

	/*
	auto txt = makeEntity();
	txt->addTag("MenuText"); 
	txt->setPosition(Vector2f(Engine::getWindowSize().x * 0.3, Engine::getWindowSize().y * 0.25));
	if (Joystick::isConnected(0)) {
		auto t = txt->addComponent<TextComponent>("Neighbourhood Nash:\n\nPress A for game\nPress B for settings\nPress X for scoreboard\nPress Y for credits");
	}
	else {
		auto t = txt->addComponent<TextComponent>("Neighbourhood Nash:\n\nPress 1 for game\nPress 2 for settings\nPress 3 for scoreboard\nPress 4 for credits");
	}
	*/

	L1.cityAtmos.stop(); 
	//Game music loop handling. 
	menuLoop.openFromFile("res/music/MainMenuLoop.mp3");
	menuLoop.setLoop(true);
	//menuLoop.setVolume(audioVol.menuLoopVolume);
	menuLoop.setVolume(70);
	menuLoop.play();

	setLoaded(true);
}

void MainMenu::UnLoad() {
	Scene::UnLoad(); 
}

void MainMenu::Render() {
	Scene::Render();
}

void MainMenu::Update(const double& dt) {

	//Keyboard
	if ((Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) && btnTimer2 <= 0) {
		btnTimer2 = 1.0f; 
		if (selectedOption - 1 >= 0) {
			menuTexts[selectedOption]->ChangeColor(sf::Color(50, 50, 50, 255));
			selectedOption--;
			menuTexts[selectedOption]->ChangeColor(Color::White); 
		}
	}

	if ((Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) && btnTimer2 <= 0) {
		btnTimer2 = 1.0f;
		if (selectedOption + 1 < menuOptions.size()) {
			menuTexts[selectedOption]->ChangeColor(sf::Color(50, 50, 50, 255));
			selectedOption++;
			menuTexts[selectedOption]->ChangeColor(Color::White);
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Enter) && btnTimer2 <= 0) {
		btnTimer2 = 1.0f; 
		menuOptions.clear(); 
		menuTexts.clear(); 
		switch (selectedOption) {
		case 0:
			Engine::ChangeScene(&L1);
			menuLoop.stop();
			break;
		case 1:
			Engine::ChangeScene(&settings);
			break;
		case 2:
			Engine::ChangeScene(&scoreboard);
			break;
		case 3:
			Engine::ChangeScene(&credits);
			break;
		default:
			break;
		}
	}

	//Joystick
	if (Joystick::isConnected(0)) {
		float joystickPovYPos = Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY); 
		if ((joystickPovYPos > 0) && btnTimer2 <= 0) {
			btnTimer2 = 1.0f;
			if (selectedOption - 1 >= 0) {
				menuTexts[selectedOption]->ChangeColor(sf::Color(50, 50, 50, 255));
				selectedOption--;
				menuTexts[selectedOption]->ChangeColor(Color::White);
			}
		}

		if ((joystickPovYPos < 0) && btnTimer2 <= 0) {
			btnTimer2 = 1.0f;
			if (selectedOption + 1 < menuOptions.size()) {
				menuTexts[selectedOption]->ChangeColor(sf::Color(50, 50, 50, 255));
				selectedOption++;
				menuTexts[selectedOption]->ChangeColor(Color::White);
			}
		}

		if (Joystick::isButtonPressed(0, 0) && btnTimer2 <= 0) {
			btnTimer2 = 1.0f;
			menuOptions.clear();
			menuTexts.clear();
			switch (selectedOption) {
			case 0:
				Engine::ChangeScene(&L1);
				menuLoop.stop();
				break;
			case 1:
				Engine::ChangeScene(&settings);
				break;
			case 2:
				Engine::ChangeScene(&scoreboard);
				break;
			case 3:
				Engine::ChangeScene(&credits);
				break;
			default:
				break;
			}
		}
	}

	btnTimer2 -= dt; 

	/*
	if (sf::Keyboard::isKeyPressed(Keyboard::Num1)) {
		Engine::ChangeScene(&L1);
		menuLoop.stop(); 
	}
	if (sf::Keyboard::isKeyPressed(Keyboard::Num2)) {
		Engine::ChangeScene(&settings);
	}
	if (sf::Keyboard::isKeyPressed(Keyboard::Num3)) {
		Engine::ChangeScene(&scoreboard);
	}
	if (sf::Keyboard::isKeyPressed(Keyboard::Num4)) {
		Engine::ChangeScene(&credits); 
	}

	if (Joystick::isConnected(0)) {
		if (sf::Joystick::isButtonPressed(0, 0)) {
			Engine::ChangeScene(&L1);
			menuLoop.setVolume(60);
		}
		if (sf::Joystick::isButtonPressed(0, 1)) {
			Engine::ChangeScene(&settings);
		}
		if (sf::Joystick::isButtonPressed(0, 2)) {
			Engine::ChangeScene(&scoreboard);
		}
		if (sf::Joystick::isButtonPressed(0, 3)) {
			Engine::ChangeScene(&credits);
		}
	}
	*/
	Scene::Update(dt);
}