#pragma once

#include "LevelSystem.h"
#include "engine.h"
#include "components/cmp_sprite.h"
#include <SFML/Audio.hpp>


//Game over scene class
class GameOver : public Scene {
protected:
	sf::SoundBuffer gameOverBuffer;
	sf::Sound gameOverSound;
public:
	GameOver() = default; 
	~GameOver() = default; 

	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;
};