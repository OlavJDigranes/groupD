#include <iostream>
#include <thread>
#include "scene_Level1.h"

const float t = 18.f;

void Level1::Load() {
	ls::loadLevelFile("res/levels/level1.txt", t);
	//ls::loadLevelFile("res/levels/TileTestLevel.txt", 50.f);

	auto ho = Engine::getWindowSize().y - (ls::getHeight() * t);
	ls::setOffset(sf::Vector2f(0, ho));

	//std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	std::cout << " Scene 1 Load Done" << std::endl;

	setLoaded(true);
}

void Level1::UnLoad() {

}

void Level1::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}

void Level1::Update(const double& dt) {
	Scene::Update(dt);
}