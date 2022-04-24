#include "cmp_player_controller.h"

PlayerController::PlayerController(Entity* p, std::weak_ptr<DrivingComponent> drive_cmp) : Component(p), _driver(drive_cmp) {
    for (unsigned int i = 0; i < sf::Joystick::Count; ++i)
    {
        if (sf::Joystick::isConnected(i))
            std::cout << "Joystick " << i << " is connected!" << std::endl;
        else
            std::cout << "Joystick " << i << " is NOT connected!" << std::endl;
    }
}

PlayerController::~PlayerController() {
	Component::~Component();
}

void PlayerController::update(double dt) {
	if (std::shared_ptr<DrivingComponent> d = _driver.lock()) {
        // Control inputs
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            d->Rotate(-180, dt);   // Turn left
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            d->Rotate(180, dt);    // Turn right
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            d->Drive(1, dt);   // Drive forwards
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            d->Brake(dt);  // Brake
        }
	}
	else {
        printf("No driving component connected. Destroying controller instance.");
		PlayerController::~PlayerController();
	}
}