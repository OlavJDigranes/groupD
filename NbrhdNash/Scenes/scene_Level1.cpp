#include <iostream>
#include <thread>
#include "scene_Level1.h"

//#define RENDER_TO_TEX
//#define DEBUG_COLLIDERS
//#define FAKE_LOADING
//#define DEBUG_BIRDS

const float t = 64.f;
static std::shared_ptr<Entity> player;
static sf::View playerView;

void Level1::Load() {
	tag = 1; 

	ls::loadLevelFile("res/levels/Level1_testing.txt", t);
#ifdef RENDER_TO_TEX
	auto ho = Engine::getWindowSize().y - (ls::getHeight() * t);
	ls::setOffset(sf::Vector2f(0, 0));
	ls::setMapPosition(sf::Vector2f(0, ho));
#endif // RENDER_TO_TEX

	// Create player entity
	{
		player = makeEntity();
		player->setPosition(ls::getTilePosition(ls::findTiles(ls::HOME)[0]) + Vector2f(20, 0));
		auto s = player->addComponent<ShapeComponent>();
		s->setShape<sf::RectangleShape>(sf::Vector2f(20.f, 30.f));
		s->getShape().setFillColor(sf::Color::White);
		s->getShape().setOrigin(sf::Vector2f(10.f, 15.f));
		
		player->addComponent<PlayerDrivingComponent>(sf::Vector2f(20.f, 30.f));
	}

	// Setting view to player's location
#ifndef RENDER_TO_TEX
	playerView = std::make_shared<sf::View>(sf::View(player->getPosition(), Vector2f(1920.f, 1080.f)));
	view = player->getPosition();
#endif // !RENDER_TO_TEX

	// Setting up colliders and sensors for statics (houses/shops etc.)
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
#ifdef DEBUG_COLLIDERS
			auto debug_shape = e->addComponent<ShapeComponent>();
			debug_shape->setShape<sf::RectangleShape>(sf::Vector2f(t, t));
			debug_shape->getShape().setFillColor(sf::Color::Cyan);
			debug_shape->getShape().setOrigin(Vector2f(t / 2, t / 2));
#endif
			e->addComponent<PhysicsComponent>(false, Vector2f(t, t));
		}
		all.clear();
		auto chkpt = ls::findTiles(ls::CHECKPOINT);
		auto shops = ls::findTiles(ls::SHOPS);
		auto grates = ls::findTiles(ls::GRATEROAD);
		all.insert(all.begin(), chkpt.begin(), chkpt.end());
		all.insert(all.begin(), shops.begin(), shops.end());
		all.insert(all.begin(), grates.begin(), grates.end()); 
		for (auto w : all) {
			auto pos = ls::getTilePosition(w);
			auto e = makeEntity();
			e->setPosition(pos);
#ifdef DEBUG_COLLIDERS
			auto debug_shape = e->addComponent<ShapeComponent>();
			debug_shape->setShape<sf::RectangleShape>(sf::Vector2f(t, t));
			debug_shape->getShape().setFillColor(sf::Color::White);
			debug_shape->getShape().setOrigin(Vector2f(t / 2, t / 2));
#endif
			if (ls::getTileAt(pos) == ls::SHOPS) {
				auto m = e->addComponent<PhysicsTriggerComponent>(Vector2f(t, t), true);
				_shops.push_back(m);
			}
			else if (ls::getTileAt(pos) == ls::CHECKPOINT) {
				auto m = e->addComponent<PhysicsTriggerComponent>(Vector2f(t, t), true);
				_goal = m;
			}
			else {
				e->addComponent<PhysicsTriggerComponent>(Vector2f(t, t), false);
			}
		}
	}

	// Setting up birds
	{
		for (auto tree : ls::findTiles(ls::BIRDSPAWN)) {
			auto enemy = makeEntity();
			enemy->setPosition(Vector2f(ls::getTilePosition(tree) + Vector2f(t/2, t/2)));
			auto s = enemy->addComponent<ShapeComponent>();
			s->setShape<CircleShape>(10.0f, 30.0f);
			s->getShape().setFillColor(Color::Blue);
			s->getShape().setOrigin(Vector2f(10.f, 10.f));
			auto bird = enemy->addComponent<SteeringComponent>(player.get(), false, Vector2i(ls::getWidth(), ls::getHeight()));
			_birds.push_back(bird);
		}
	}

	{
		std::vector<Vector2ul> cars;
		auto cars_1 = ls::findTiles(ls::CAR1SPAWN);
		auto cars_2 = ls::findTiles(ls::CAR2SPAWN);
		auto cars_3 = ls::findTiles(ls::CAR3SPAWN);
		cars.insert(cars.begin(), cars_1.begin(), cars_1.end());
		cars.insert(cars.begin(), cars_2.begin(), cars_2.end());
		cars.insert(cars.begin(), cars_3.begin(), cars_3.end());
		for (auto c : cars) {
			auto car = makeEntity();
			auto pos = ls::getTilePosition(c) + Vector2f(t/2, t/2);
			car->setPosition(pos);
			auto cmp = car->addComponent<ShapeComponent>();
			cmp->setShape<sf::RectangleShape>(sf::Vector2f(20.f, 30.f));
			cmp->getShape().setFillColor(sf::Color::Red);
			cmp->getShape().setOrigin(sf::Vector2f(10.f, 15.f));
		}
	}

	// Debug setting to fake a loading screen
#ifdef FAKE_LOADING
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
#endif // FAKE_LOADING

	std::cout << " Scene 1 Load Done" << std::endl;

	setLoaded(true);
}

void Level1::UnLoad() {
	_shops.clear();
	_birds.clear();
	_goal = nullptr;
	Engine::GetWindow().setView(Engine::GetWindow().getDefaultView());
	player.reset();
	ls::unload();
	Scene::UnLoad();
}

void Level1::Render() {
#ifndef RENDER_TO_TEX
	playerView->setCenter(view);
	Engine::GetWindow().setView(*playerView);
#endif // !RENDER_TO_TEX

	ls::render(Engine::GetWindow());
	Scene::Render();
}

void Level1::Update(const double& dt) {
	// Update view to stay within map bounds
#ifndef RENDER_TO_TEX
	if (player->getPosition().x > 960 && player->getPosition().x < 2880) {
		view.x = player->getPosition().x;
	}
	else {
		player->getPosition().x > 960 ? view.x = 2880 : view.x = 960;
	}
	if (player->getPosition().y > 540 && player->getPosition().y < 3300) {
		view.y = player->getPosition().y;
	}
	else {
		player->getPosition().y > 540 ? view.y = 3300 : view.y = 540;
	}
#endif // !RENDER_TO_TEX
	// Goal checking for arrival at correct shop
	if (_goal->HasGoalBeenReached()) {
		printf("Reached checkpoint! Turn back and head home to deliver the shopping.");
	}
	// Debug birds chasing player
#ifdef DEBUG_BIRDS
	if (Keyboard::isKeyPressed(Keyboard::B)) {
		for (auto b : _birds) {
			b->SetActive(true);
		}
	}
#endif
	
	ls::updateMap();
	ents.mapPosition = ls::getMapMovement();
	Scene::Update(dt);
}