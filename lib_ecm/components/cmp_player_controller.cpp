#include "cmp_player_controller.h"

using namespace std; 
using namespace sf; 

PlayerController::PlayerController(Entity* p, std::weak_ptr<DrivingComponent> drive_cmp) : Component(p), _driver(drive_cmp) {
    for (unsigned int i = 0; i < sf::Joystick::Count; ++i)
    {
        if (sf::Joystick::isConnected(i))
            std::cout << "Joystick " << i << " is connected!" << std::endl;
        else
            std::cout << "Joystick " << i << " is NOT connected!" << std::endl;
    }    

    //Driving sound
    carEngineBuffer.loadFromFile("res/music/CarSound.mp3");
    carEngine.setBuffer(carEngineBuffer);
    carEngine.setVolume(90);
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
            //Driving sound
            soundOn = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            d->Brake(dt);  // Brake
            soundOn = false;
        }

        sf::Joystick::Identification joystickID = sf::Joystick::getIdentification(0);
        if (Joystick::isConnected(0)) {
            float joystickXYAxisPos = Joystick::getAxisPosition(0, sf::Joystick::Axis::X);
            float joystickTAxisPos = Joystick::getAxisPosition(0, sf::Joystick::Axis::Z);
            if (joystickXYAxisPos < -50.0f) {
                d->Rotate(-180, dt);   // Turn left
            }
            if (joystickXYAxisPos > 50.0f) {
                d->Rotate(180, dt);    // Turn right
            }
            if (joystickTAxisPos < 0) {
                d->Drive(1, dt);   // Drive forwards
            }
            if (joystickTAxisPos > 0) {
                d->Brake(dt);  // Brake
            }
        }

        //Car sounds
        if (soundOn) {
            std::cout << "wg" << std::endl;
            carEngine.play();
            //carEngine.setLoop(true);
        }
        if (!soundOn) {
            std::cout << "rh" << std::endl;
            carEngine.stop();
        }
	}
	else {
        printf("No driving component connected. Destroying controller instance.");
		PlayerController::~PlayerController();
	}
}