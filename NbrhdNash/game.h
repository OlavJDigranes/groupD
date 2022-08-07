#pragma once

#include "Scenes/scene_MainMenu.h"
#include "Scenes/scene_Level1.h"
#include "Scenes/scene_Credits.h"
#include "Scenes/scene_Settings.h"
#include "Scenes/scene_Celebration.h"
#include "Scenes/scene_GameOver.h"
#include "Scenes/scene_Steering.h"
#include "Scenes/scene_Scoreboard.h"
#include "Scenes/scene_AudioSettings.h"
#include "Scenes/scene_ControlSettings.h"
#include "Scenes/scene_VisualSettings.h"
#include <SFML/Audio.hpp>

using namespace sf;

extern MainMenu menu;
extern Level1 L1;
extern Credits credits;
extern Settings settings; 
extern GameOver gameover;
extern Celebration celebration; 
extern SteeringScene steering; 
extern Scoreboard scoreboard; 
extern AudioSettings audioSettings; 
extern ControlSettings controlSettings; 
extern VisualSettings visualSettings; 
