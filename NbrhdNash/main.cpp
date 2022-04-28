#include <SFML/Graphics.hpp>
#include "LevelSystem.h"
#include "engine.h"
#include "Scenes/scene_Level1.h"
#include "game.h"
#include "Scenes/scene_Settings.h"

std::unique_ptr<sf::RenderWindow> window;
const int gameWidth = 1920; // change to file read values
const int gameHeight = 1080;

MainMenu menu; 
Level1 L1;
Credits credits;
Settings settings; 
Celebration celebration;
GameOver gameover; 
SteeringScene steering; 
Scoreboard scoreboard;

int main() {
	Engine::Start(gameWidth, gameHeight, "Neighbourhood Nash!", &menu);
	settings.setSavedSettings();
}