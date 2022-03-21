#include <SFML/Graphics.hpp>
#include "LevelSystem.h"

std::unique_ptr<sf::RenderWindow> window;
const int gameWidth = 1920; // change to file read values
const int gameHeight = 1080;
 
void Load() {
	window = std::make_unique<sf::RenderWindow>();
	window->create(sf::VideoMode(gameWidth, gameHeight), "Neighbourhood Nash!");
}

void Render() {
	window->clear();

	//Render

	window->display();
}

void Shutdown() {
	//activeScene->Shutdown(); //Empties all entities safely and such
	window->close();
}

void Update() {

}

int main() {
	static sf::Clock clock;
	Load();

	while (window->isOpen()) {
		float dt = clock.restart().asSeconds();

		sf::Event winEvent;
		if (window->pollEvent(winEvent)) {
			if (winEvent.type == sf::Event::Closed) {
				Shutdown();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			Shutdown();
		}
	}
}