#pragma once

#include "LevelSystem.h"
#include "engine.h"
#include "components/components.h"

class Level1 : public Scene {
protected:
	std::shared_ptr<sf::View> playerView;
	Vector2f view;
	std::map<string, std::shared_ptr<sf::Texture>> _textures{
		{"res/img/player.jpg", std::make_shared<sf::Texture>()},
		{"res/img/house.jpg", std::make_shared<sf::Texture>()},
		{"res/img/grass.jpg", std::make_shared<sf::Texture>()},
		{"res/img/tree.jpg", std::make_shared<sf::Texture>()},
		{"res/img/grateRoad.jpg", std::make_shared<sf::Texture>()},
		{"res/img/road.jpg", std::make_shared<sf::Texture>()},
		{"res/img/parking.jpg", std::make_shared<sf::Texture>()},
		{"res/img/shop.jpg", std::make_shared<sf::Texture>()},
		{"res/img/pigeon.jpg", std::make_shared<sf::Texture>()},
		{"res/img/car_blue.jpg", std::make_shared<sf::Texture>()}
	};
	std::vector<std::shared_ptr<PhysicsTriggerComponent>> _shops;
	std::shared_ptr<PhysicsTriggerComponent> _goalShop;
	std::shared_ptr<PhysicsTriggerComponent> _home;
	std::vector<std::shared_ptr<Entity>> *_birds = new std::vector<std::shared_ptr<Entity>>();
	std::shared_ptr<LevelTimer> _timer;
	std::shared_ptr<PlayerDataComponent> _playerData;
	bool _reachedShop;
	bool _complete;
	bool _hasFailed;
public:
	bool IsCompleted() { return _complete; }

	bool HasFailedLevel () { return _hasFailed; }

	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;
};