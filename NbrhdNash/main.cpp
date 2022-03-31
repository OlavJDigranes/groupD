#include <SFML/Graphics.hpp>
#include "LevelSystem.h"
#include "engine.h"
#include "Scenes/scene_Level1.h"

std::unique_ptr<sf::RenderWindow> window;
const int gameWidth = 1920; // change to file read values
const int gameHeight = 1080;

Level1 L1;

int main() {
	Engine::Start(gameWidth, gameHeight, "Neighbourhood Nash!", &L1);
}