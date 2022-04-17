#include <iostream>
#include <thread>
#include "scene_Level1.h"

const float t = 64.f;
static std::shared_ptr<Entity> player;
static sf::View playerView;

void Level1::Load() {
	tag = 1; 

	ls::loadLevelFile("res/levels/Level1_testing.txt", t);
	auto ho = Engine::getWindowSize().y - (ls::getHeight() * t);
	ls::setOffset(sf::Vector2f(0, 0));
#ifdef RENDER_TO_TEX
	ls::setMapPosition(sf::Vector2f(0, ho));
#endif // RENDER_TO_TEX

	{
		player = makeEntity();
		player->setPosition(ls::getTilePosition(ls::findTiles(ls::HOME)[0]) + Vector2f(20, 0));
		auto s = player->addComponent<ShapeComponent>();
		s->setShape<sf::RectangleShape>(sf::Vector2f(20.f, 30.f));
		s->getShape().setFillColor(sf::Color::White);
		s->getShape().setOrigin(sf::Vector2f(10.f, 15.f));
		
		player->addComponent<PlayerDrivingComponent>(sf::Vector2f(20.f, 30.f));
	}

	playerView = std::make_shared<sf::View>(sf::View(player->getPosition(), Vector2f(1920.f, 1080.f)));
	
	{
		std::vector<Vector2ul> all;
		auto walls = ls::findTiles(ls::EDGEWALL);
		auto emptyHouses = ls::findTiles(ls::EMPTYHOUSE);
		auto neighbourHouses = ls::findTiles(ls::NEIGHBOURHOUSE);
		all.insert(all.begin(), walls.begin(), walls.end());
		all.insert(all.begin(), emptyHouses.begin(), emptyHouses.end());
		all.insert(all.begin(), neighbourHouses.begin(), neighbourHouses.end());
		for (auto w : all) {
			auto pos = ls::getTilePosition(w);
			auto e = makeEntity();
			e->setPosition(pos);
#ifdef DEBUG_HOUSECOL
			auto debug_shape = e->addComponent<ShapeComponent>();
			debug_shape->setShape<sf::RectangleShape>(sf::Vector2f(t, t));
			debug_shape->getShape().setFillColor(sf::Color::Cyan);
			debug_shape->getShape().setOrigin(Vector2f(t / 2, t / 2));
#endif
			e->addComponent<PhysicsComponent>(false, Vector2f(t, t));
		}
	}
	//std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	std::cout << " Scene 1 Load Done" << std::endl;

	setLoaded(true);
}

void Level1::UnLoad() {
	Engine::GetWindow().setView(Engine::GetWindow().getDefaultView());
	player.reset();
	ls::unload();
	Scene::UnLoad();
}

void Level1::Render() {
#ifndef RENDER_TO_TEX
	playerView->setCenter(player->getPosition());
	Engine::GetWindow().setView(*playerView);
#endif // !RENDER_TO_TEX

	ls::render(Engine::GetWindow());
	Scene::Render();
}

void Level1::Update(const double& dt) {
	ls::updateMap();
	ents.mapPosition = ls::getMapMovement();
	Scene::Update(dt);
}