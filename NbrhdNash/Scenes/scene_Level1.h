#pragma once

#include "LevelSystem.h"
#include "engine.h"
#include "components/components.h"

class Level1 : public Scene {
protected:
	std::shared_ptr<sf::View> playerView;
public:
	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;
};