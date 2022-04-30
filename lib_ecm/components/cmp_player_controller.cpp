#include "cmp_player_controller.h"

using namespace std; 
using namespace sf; 

PlayerController::PlayerController(Entity* p, std::weak_ptr<DrivingComponent> drive_cmp) : Component(p), _driver(drive_cmp) {
    
    /*
    for (unsigned int i = 0; i < sf::Joystick::Count; ++i)
    {
        if (sf::Joystick::isConnected(i))
            std::cout << "Joystick " << i << " is connected!" << std::endl;
        else
            std::cout << "Joystick " << i << " is NOT connected!" << std::endl;
    }    
    */

    //Driving sound
    carEngineBuffer.loadFromFile("res/music/CarSound.mp3");
    carEngine.setBuffer(carEngineBuffer);
    carEngine.setVolume(70);
    
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
            d->Drive(3, dt);   // Drive forwards
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
                d->Drive(3, dt);   // Drive forwards
                soundOn = true;
            }
            if (joystickTAxisPos > 0) {
                d->Brake(dt);  // Brake
                soundOn = false;
            }
        }

        //Car sounds
        if (soundOn && !soundCheck) {
            carEngine.play();
            carEngine.setLoop(true);
            soundCheck = true;
        }
        if (!soundOn && soundCheck) {
            carEngine.stop();
            soundCheck = false;
        }
	}
	else {
        //printf("No driving component connected. Destroying controller instance.");
		PlayerController::~PlayerController();
	}
}