#include <iostream>
#include <thread>
#include "scene_Level1.h"

void Level1::Load() {
	ls::loadLevelFile("res/levels/level1.txt", 50.f);
}

void Level1::UnLoad() {

}

void Level1::Render() {
	Scene::Render();
}

void Level1::Update(const double& dt) {
	Scene::Update(dt);
}