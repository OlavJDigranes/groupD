#pragma once

#include <SFML/Audio.hpp>
#include "engine.h"

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