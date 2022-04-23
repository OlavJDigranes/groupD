#pragma once

#include <SFML/Audio.hpp>
#include "engine.h"

//Main menu scene class with music loop
class MainMenu : public Scene {
protected:
	sf::Music menuLoop;

public:
	MainMenu() = default;
	~MainMenu() = default;

	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;
};