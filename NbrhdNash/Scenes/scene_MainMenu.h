#pragma once

#include <SFML/Audio.hpp>
#include "engine.h"
#include "SFML/Window.hpp"
#include "SFML/Window/Joystick.hpp"
#include "components/components.h"

//Main menu scene class with music loop
class MainMenu : public Scene {
protected:
	sf::Music menuLoop;
	sf::Joystick::Identification joystickID = sf::Joystick::getIdentification(0);
	int selectedOption; 
	std::vector<std::shared_ptr<Entity>> menuOptions;
	std::vector<std::shared_ptr<TextComponent>> menuTexts;
	float btnTimer2 = 1.0f;

public:
	MainMenu() = default;
	~MainMenu() = default;

	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;
};