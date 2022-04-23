#include "cmp_player_controller.h"

PlayerController::PlayerController(Entity* p, std::weak_ptr<DrivingComponent> drive_cmp) : Component(p), _driver(drive_cmp) {}

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