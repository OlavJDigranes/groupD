#pragma once

#include "../lib_ecm/ecm.h"
#include "cmp_drive.h"
#include "SFML/Window.hpp"
#include "SFML/Window/Joystick.hpp"
#include <SFML/Audio.hpp>

class PlayerController : public Component {
protected:
	std::weak_ptr<DrivingComponent> _driver;

	//Driving sound
	sf::SoundBuffer carEngineBuffer;
	sf::Sound carEngine;
	bool soundOn = false;
	bool soundCheck = false; 
public:
	void update(double) override;
	void render() override {};
	explicit PlayerController(Entity* p, std::weak_ptr<DrivingComponent> drive_cmp);
	~PlayerController();
};