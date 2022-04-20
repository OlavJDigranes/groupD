#pragma once

#include "LevelSystem.h"
#include "engine.h"
#include "components/components.h"

class Level1 : public Scene {
protected:
	std::shared_ptr<sf::View> playerView;
	Vector2f view;
	std::vector<std::shared_ptr<PhysicsTriggerComponent>> _shops;
	std::shared_ptr<PhysicsTriggerComponent> _goalShop;
	std::shared_ptr<PhysicsTriggerComponent> _home;
	std::vector<std::shared_ptr<SteeringComponent>> _birds;
	std::shared_ptr<LevelTimer> _timer;
	bool _reachedShop;
public:
	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;
};