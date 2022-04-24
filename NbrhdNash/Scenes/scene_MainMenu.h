#pragma once

#include <SFML/Audio.hpp>
#include "engine.h"
#include "SFML/Window.hpp"
#include "SFML/Window/Joystick.hpp"

class MainMenu : public Scene {
protected:
	sf::Music menuLoop;
	sf::Joystick::Identification joystickID = sf::Joystick::getIdentification(0);

public:
	MainMenu() = default;
	~MainMenu() = default;

	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;
};