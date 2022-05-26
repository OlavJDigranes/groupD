#include "scene_Settings_Audio.h"
#include "scene_Settings.h"

using namespace std;
using namespace sf; 

void SettingsAudio::Load() {
	tag = -11; 

	sf::Joystick::Identification joystickID = sf::Joystick::getIdentification(0);

	auto esc = makeEntity();
	esc->setPosition(Vector2f(5, 5));
	if (Joystick::isConnected(0)) {
		auto y = esc->addComponent<ESCTextComponent>("Press Start to exit the game\nPress A to select a menu option");
	}
	else {
		auto y = esc->addComponent<ESCTextComponent>("Press ESC to return to the menu\nPress Enter to select a menu option");
	}

	//Settings texts from settings scene
	constexpr int optionNmbS = 4;
	const string options[optionNmbS] = { "Audio","Controls","Video","Back" };
	//selectedOption2 = 0;

	auto titleText = makeEntity();
	titleText->setPosition(Vector2f(Engine::getWindowSize().x * 0.2, Engine::getWindowSize().y * 0.25));
	auto u = titleText->addComponent<TextComponent>("Settings & Help");
	float txtOffset = 0.0f;
	for (int i = 0; i < optionNmbS; i++) {
		settingsOptions.push_back(makeEntity());
		settingsTexts.push_back(settingsOptions[i]->addComponent<TextComponent>(options[i]));
		if (i != 0) {
			settingsTexts[i]->ChangeColor(sf::Color(50, 50, 50, 255));
		}
		txtOffset -= 35.0f;
		settingsOptions[i]->setPosition(Vector2f(Engine::getWindowSize().x * 0.2, (Engine::getWindowSize().y * 0.25) - txtOffset));
	}
	settingsTexts[0]->ChangeColor(sf::Color::White); 

	//audio settings texts. 
	constexpr int optionNmb = 3;
	const string options[optionNmb] = { "Main Menu: " + std::to_string(menuLoopVolume),"SFX Modifier: " + std::to_string(sfxVolumeMod),"Ambiance Modifier: " + std::to_string(ambienceVolumeMod) };
	selectedOption3 = 0;

	auto titleText = makeEntity();
	titleText->setPosition(Vector2f(Engine::getWindowSize().x * 0.5, Engine::getWindowSize().y * 0.25));
	auto u = titleText->addComponent<TextComponent>("Volume Settings");
	float txtOffset = 0.0f;
	for (int i = 0; i < optionNmb; i++) {
		audioOptions.push_back(makeEntity());
		audioTexts.push_back(audioOptions[i]->addComponent<TextComponent>(options[i]));
		if (i != 0) {
			audioTexts[i]->ChangeColor(sf::Color(50, 50, 50, 255));
		}
		txtOffset -= 35.0f;
		audioOptions[i]->setPosition(Vector2f(Engine::getWindowSize().x * 0.2, (Engine::getWindowSize().y * 0.25) - txtOffset));
	}

	setLoaded(true); 
}

void SettingsAudio::UnLoad() {
	Scene::UnLoad();
}

void SettingsAudio::Update(const double& dt) {
	Scene::Update(dt); 
}

void SettingsAudio::Render() {
	Scene::Render(); 
}