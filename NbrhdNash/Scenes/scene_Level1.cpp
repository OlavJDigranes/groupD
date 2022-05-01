#include <iostream>
#include <thread>
#include "scene_Level1.h"

//#define RENDER_TO_TEX
//#define DEBUG_COLLIDERS
//#define FAKE_LOADING
//#define DEBUG_BIRDS

const float t = 128.f;
static std::shared_ptr<Entity> player;
static sf::View playerView;

void Level1::Load() {
	tag = 1; 

	for (auto tex : _textures) {
		if (tex.second->loadFromFile(tex.first)) {
			tex.second->loadFromFile(tex.first);
		}
	}

	//ls::loadLevelFile("res/levels/Level1_testing.txt", t);
	ls::loadLevelFile("res/levels/level1.txt", t);
	ls::setOffset(sf::Vector2f(0, 0));
#ifdef RENDER_TO_TEX
	auto ho = Engine::getWindowSize().y - (ls::getHeight() * t);
	ls::setOffset(sf::Vector2f(0, 0));
	ls::setMapPosition(sf::Vector2f(0, ho));
#endif // RENDER_TO_TEX

	// Grass textures
	{
		std::vector<Vector2ul> all{};
		auto grass = ls::findTiles(ls::GRASS);
		auto trees = ls::findTiles(ls::TREE);
		auto birdspawns = ls::findTiles(ls::BIRDSPAWN);
		all.insert(all.begin(), grass.begin(), grass.end());
		all.insert(all.begin(), trees.begin(), trees.end());
		all.insert(all.begin(), birdspawns.begin(), birdspawns.end());
		for (auto a : all) {
			auto pos = ls::getTilePosition(a);
			auto e = makeEntity();
			e->setPosition(pos);
			auto tx = e->addComponent<SpriteComponent>(true);
			if (ls::getTile(a) == ls::GRASS) {
				tx->setTexture(_textures["res/img/grass.jpg"]);
			}
			else {
				tx->setTexture(_textures["res/img/tree.jpg"]);
				auto p = e->addComponent<PhysicsComponent>(false, Vector2f(t, t));
			}
		}
	}

	// Road textures
	{
		std::vector<Vector2ul> all{};
		auto roads = ls::findTiles(ls::ROAD);
		auto chk1 = ls::findTiles(ls::AICHECKPOINT1);
		auto chk2 = ls::findTiles(ls::AICHECKPOINT2);
		auto chk3 = ls::findTiles(ls::AICHECKPOINT3);
		auto chk4 = ls::findTiles(ls::AICHECKPOINT4);
		auto chk5 = ls::findTiles(ls::AICHECKPOINT5);
		all.insert(all.begin(), roads.begin(), roads.end());
		all.insert(all.begin(), chk1.begin(), chk1.end());
		all.insert(all.begin(), chk2.begin(), chk2.end());
		all.insert(all.begin(), chk3.begin(), chk3.end());
		all.insert(all.begin(), chk4.begin(), chk4.end());
		all.insert(all.begin(), chk5.begin(), chk5.end());
		for (auto a : all) {
			auto pos = ls::getTilePosition(a);
			auto e = makeEntity();
			e->setPosition(pos);
			auto tx = e->addComponent<SpriteComponent>(true);
			tx->setTexture(_textures["res/img/road.jpg"]);
		}
		all.clear();
		auto park = ls::findTiles(ls::PARKINGSPACE);
		auto car1 = ls::findTiles(ls::CAR1SPAWN);
		auto car2 = ls::findTiles(ls::CAR2SPAWN);
		auto car3 = ls::findTiles(ls::CAR3SPAWN);
		all.insert(all.begin(), park.begin(), park.end());
		all.insert(all.begin(), car1.begin(), car1.end());
		all.insert(all.begin(), car2.begin(), car2.end());
		all.insert(all.begin(), car3.begin(), car3.end());
		for (auto p : all) {
			auto pos = ls::getTilePosition(p);
			auto e = makeEntity();
			e->setPosition(pos);
			auto tx = e->addComponent<SpriteComponent>(true);
			tx->setTexture(_textures["res/img/parking.jpg"]);
		}
	}


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
			if (ls::getTileAt(pos) == ls::EMPTYHOUSE || ls::getTileAt(pos) == ls::NEIGHBOURHOUSE) {
				auto t = e->addComponent<SpriteComponent>(true);
				t->setTexture(_textures["res/img/house.jpg"]);
				if (ls::getTileAt(pos) == ls::NEIGHBOURHOUSE) {
					auto ft = e->addComponent<FadingTexture>(true);
					ft->setTexture(_textures["res/img/alert.png"]);
					_nbrs->push_back(e);
				}
			}
			if (ls::getTileAt(pos) == ls::EDGEWALL) {
				auto t = e->addComponent<SpriteComponent>(true);
				t->setTexture(_textures["res/img/tree.jpg"]);
			}
		}
		all.clear();
		auto chkpt = ls::findTiles(ls::CHECKPOINT);
		auto shops = ls::findTiles(ls::SHOPS);
		auto grates = ls::findTiles(ls::GRATEROAD);
		auto home = ls::findTiles(ls::HOME);
		all.insert(all.begin(), chkpt.begin(), chkpt.end());
		all.insert(all.begin(), shops.begin(), shops.end());
		all.insert(all.begin(), grates.begin(), grates.end());
		all.insert(all.begin(), home.begin(), home.end());
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
				auto m = e->addComponent<PhysicsTriggerComponent>(Vector2f(t, t), false, true);
				_shops.push_back(m);
				auto tex = e->addComponent<SpriteComponent>(true);
				tex->setTexture(_textures["res/img/shop.jpg"]);
			}
			else if (ls::getTileAt(pos) == ls::GRATEROAD) {
				auto m = e->addComponent<GrateComponent>(Vector2f(t, t), _birds, _nbrs);
				_grates.push_back(m);
				auto sp = e->addComponent<SpriteComponent>(true);
				sp->setTexture(_textures["res/img/grateRoad.jpg"]);
#ifdef DEBUG_GRATE_TRIGGER_RADIUS
				auto dbg_m = e->addComponent<ShapeComponent>();
				dbg_m->setShape<sf::CircleShape>(1.0f, 30.f);
				dbg_m->getShape().setFillColor(sf::Color::Green);
				m->ConsumeDebugCmp(dbg_m);
#endif
			}
			else if (ls::getTileAt(pos) == ls::CHECKPOINT) {
				auto m = e->addComponent<PhysicsTriggerComponent>(Vector2f(t, t), true, true);
				_goalShop = m;
				auto tex = e->addComponent<SpriteComponent>(true);
				tex->setTexture(_textures["res/img/shop.jpg"]);
			}
			else if (ls::getTileAt(pos) == ls::HOME) {
				_home = e->addComponent<PhysicsTriggerComponent>(Vector2f(t, t), true, false);
				auto t = e->addComponent<SpriteComponent>(true);
				t->setTexture(_textures["res/img/house.jpg"]);
			}
			else {
				e->addComponent<PhysicsTriggerComponent>(Vector2f(t, t), false, true);
			}
		}
		

	}

	// Setting up cars
	{
		std::vector<Vector2ul> cars;
		auto cars_1 = ls::findTiles(ls::CAR1SPAWN);
		auto cars_2 = ls::findTiles(ls::CAR2SPAWN);
		auto cars_3 = ls::findTiles(ls::CAR3SPAWN);
		cars.insert(cars.begin(), cars_1.begin(), cars_1.end());
		cars.insert(cars.begin(), cars_2.begin(), cars_2.end());
		cars.insert(cars.begin(), cars_3.begin(), cars_3.end());
#if 1
		for (auto c : cars) {
			auto car = makeEntity();
			auto pos = ls::getTilePosition(c) + Vector2f(t / 2, t / 2);
			car->setPosition(pos);
			auto shp = car->addComponent<ShapeComponent>();
			car->addComponent<AIDrivingComponent>(sf::Vector2f(24.f, 36.f), 20);
			auto t = car->addComponent<SpriteComponent>(true);
			t->getSprite().setOrigin(sf::Vector2f(12.f, 16.f));
			auto rng = rand() % 100;
			if (rng <= 30) {
				t->setTexture(_textures["res/img/car_green.png"]);
			}
			else if (rng <= 60) {
				t->setTexture(_textures["res/img/car_red.png"]);
			}
			else {
				t->setTexture(_textures["res/img/car_purple.png"]);
			}
		}
#else // 0

		auto car = makeEntity();
		auto pos = ls::getTilePosition(cars.at(3)) + Vector2f(t / 2, t / 2);
		car->setPosition(pos);
		auto shp = car->addComponent<ShapeComponent>();
		shp->setShape<sf::RectangleShape>(sf::Vector2f(24.f, 36.f));
		shp->getShape().setFillColor(sf::Color::Red);
		shp->getShape().setOrigin(sf::Vector2f(12.f, 16.f));
		auto ai = car->addComponent<AIDrivingComponent>(sf::Vector2f(24.f, 36.f), 20);
#endif
#ifdef DEBUG_AI_PATH
		auto debugPath = *ai->getPath();
		for (auto p : debugPath) {
			auto pos = p.worldPos + Vector2f(t / 2, t / 2);
			auto e = makeEntity();
			e->setPosition(pos);
			auto shp = e->addComponent<ShapeComponent>();
			shp->setShape<sf::CircleShape>(5.f, 30.f);
			if (!p.turnLeft) {
				shp->getShape().setFillColor(Color::Yellow);
			}
			else {
				shp->getShape().setFillColor(Color::Red);
			}
			shp->getShape().setOrigin(Vector2f(5.f, 5.f));
		}
#endif // DEBUG_AI_PATH
	}

	// Create player entity
	{
		player = makeEntity();
		player->setPosition(ls::getTilePosition(ls::findTiles(ls::HOME)[0]) + Vector2f(24, 0));
		auto t = player->addComponent<SpriteComponent>(true);
		t->setTexture(_textures["res/img/car_blue.png"]);
		t->getSprite().setOrigin(sf::Vector2f(12.f, 16.f));

		auto d = player->addComponent<DrivingComponent>(sf::Vector2f(24.f, 36.f), "Player", 24);
		player->addComponent<PlayerController>(d);
		_playerData = player->addComponent<PlayerDataComponent>(100, 100, _textures["res/img/heart_full.png"]);
		for (auto g : _grates) {
			g->SetPlayerData(_playerData);
		}

	}

	// Setting view to player's location
#ifndef RENDER_TO_TEX
	playerView = std::make_shared<sf::View>(sf::View(player->getPosition(), Vector2f(Engine::getWindowSize().x, Engine::getWindowSize().y)));
	view = player->getPosition();
#endif // !RENDER_TO_TEX

	// Setting up birds
	{
		for (auto tree : ls::findTiles(ls::BIRDSPAWN)) {
			auto enemy = makeEntity();
			_birds->push_back(enemy);
			enemy->setPosition(Vector2f(ls::getTilePosition(tree) + Vector2f(t / 2, t / 2)));
			auto s = enemy->addComponent<ShapeComponent>();
			//s->setShape<CircleShape>(10.0f, 30.0f);
			//s->getShape().setFillColor(Color::Blue);
			//s->getShape().setOrigin(Vector2f(10.f, 10.f));
			auto bird = enemy->addComponent<AIBirdComponent>(player, Vector2i(ls::getWidth() * ls::getTileSize(), ls::getHeight() * ls::getTileSize()), sf::Vector2f(10.f, 10.f));
			auto texture = enemy->addComponent<SpriteComponent>(true);
			texture->setTexture(_textures["res/img/pigeon1.png"]);
			texture->getSprite().setOrigin(sf::Vector2f(16.f, 16.f));
		}
	}


	_timer = player->addComponent<LevelTimer>(tag);
	_reachedShop = false;
	_complete = false;

	// Debug setting to fake a loading screen
#ifdef FAKE_LOADING
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
#endif // FAKE_LOADING

	std::cout << " Scene 1 Load Done" << std::endl;

	//City atmos Sound:
	cityAtmos.openFromFile("res/music/CityAtmos.mp3");
	cityAtmos.setLoop(true); 
	cityAtmos.play(); 
	cityAtmos.setVolume(10); 

	setLoaded(true);
}

void Level1::UnLoad() {
	for (auto tex : _textures) {
		tex.second.reset();
	}
	_birds->clear();
	for (auto b : *_birds) {
		b = nullptr;
	}
	_grates.clear();
	_shops.clear();
	_goalShop = nullptr;
	_home = nullptr;
	_timer = nullptr;
	Engine::GetWindow().setView(Engine::GetWindow().getDefaultView());
	player.reset();
	player = nullptr;
	_playerData = nullptr;
	playerView = nullptr;
	_reachedShop = false;
	_complete = false;
	_hasFailed = false;
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
	// TODO: Update this to use view x and y, if greater than half res or if less than map max x/y minus half res x/y
	if (player->getPosition().x > Engine::getWindowSize().x/2 && player->getPosition().x < (ls::getWidth() * ls::getTileSize()) - Engine::getWindowSize().x/2) {
		view.x = player->getPosition().x;
	}
	else {
		player->getPosition().x > Engine::getWindowSize().x / 2 ? view.x = (ls::getWidth() * ls::getTileSize()) - Engine::getWindowSize().x/2 : view.x = Engine::getWindowSize().x / 2;
	}
	if (player->getPosition().y > Engine::getWindowSize().y / 2 && player->getPosition().y < (ls::getWidth() * ls::getTileSize()) - Engine::getWindowSize().y/2) {
		view.y = player->getPosition().y;
	}
	else {
		player->getPosition().y > Engine::getWindowSize().y / 2 ? view.y = (ls::getWidth() * ls::getTileSize()) - Engine::getWindowSize().y/2 : view.y = Engine::getWindowSize().y / 2;
	}
#endif // !RENDER_TO_TEX
	// Goal checking for arrival at correct shop
	if (_goalShop->HasGoalBeenReached() && _reachedShop == false) {
		_reachedShop = true;
		//printf("Reached checkpoint! Turn back and head home to deliver the shopping.");
		_home->SetActive(true);
		_goalShop->SetActive(false);
	}
	if (_home->HasGoalBeenReached() && _reachedShop == true && _complete == false) {
		if (_home->HasGoalBeenReached()) {
			_timer->LevelTimerStop();
			_complete = true;
		}
	}
	if (_playerData->GetHealth() <= 0 || _playerData->getReputation() <= 0) {
		_hasFailed = true;
	}

	// Debug birds chasing player
#ifdef DEBUG_BIRDS
	if (Keyboard::isKeyPressed(Keyboard::B)) {
		for (auto b : _birds) {
			b->SetActive(true);
		}
	}
#endif
	// Debug birds chasing player
#ifdef DEBUG_TELEPORT
	if (Keyboard::isKeyPressed(Keyboard::LBracket)) {
		auto d = player->GetCompatibleComponent<DrivingComponent>();
		d.at(0)->teleport(ls::getTilePosition(ls::findTiles(ls::CHECKPOINT)[0]));
	}
	if (Keyboard::isKeyPressed(Keyboard::RBracket)) {
		auto d = player->GetCompatibleComponent<DrivingComponent>();
		d.at(0)->teleport(ls::getTilePosition(ls::findTiles(ls::HOME)[0]));
	}
#endif
	
	//ls::updateMap();
	//ents.mapPosition = ls::getMapMovement();
	Scene::Update(dt);
}