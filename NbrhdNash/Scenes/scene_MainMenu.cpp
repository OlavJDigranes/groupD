#include <iostream>
#include <thread>
#include "LevelSystem.h"
#include "scene_MainMenu.h"

void MainMenu::Load() {
	ls::loadLevelFile("res/levels/level1.txt", 50.f);
}

void MainMenu::UnLoad() {

}

void MainMenu::Render() {

}

void MainMenu::Update(const double& dt) {

}