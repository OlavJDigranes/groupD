#pragma once

#include "LevelSystem.h"
#include "engine.h"
#include "components/components.h"

class Level1 : public Scene {
protected:
	std::shared_ptr<sf::View> playerView;
	Vector2f view;
	std::vector<std::shared_ptr<PhysicsTriggerComponent>> _shops;
	std::shared_ptr<PhysicsTriggerComponent> _goal;
	std::vector<std::shared_ptr<SteeringComponent>> _birds;
public:
	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;
};