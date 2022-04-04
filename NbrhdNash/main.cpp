#include <SFML/Graphics.hpp>
#include "LevelSystem.h"
#include "engine.h"
#include "Scenes/scene_Level1.h"
#include "game.h"

std::unique_ptr<sf::RenderWindow> window;
const int gameWidth = 1920; // change to file read values
const int gameHeight = 1080;

MainMenu menu; 
Level1 L1;
Credits credits;
Settings settings; 

int main() {
	Engine::Start(gameWidth, gameHeight, "Neighbourhood Nash!", &menu);
}