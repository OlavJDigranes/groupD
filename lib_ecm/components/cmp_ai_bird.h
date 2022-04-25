#pragma once
#include "../lib_ecm/ecm.h"
#include "../components/cmp_ai_steering.h"
#include "maths.h"

class AIBirdComponent : Component {
protected:
	std::unique_ptr<SteeringComponent> _str;
	b2Body* _body;
	b2Fixture* _fixture;
	bodyUserData* _data;
	std::vector<const b2Contact const*> _dirtyCheck;
	bool _isChasing;
	sf::Vector2f homeLoc;
public:
	AIBirdComponent() = delete;
	explicit AIBirdComponent(Entity* p, Entity* player, sf::Vector2i levelBounds, sf::Vector2f size);
	void AwaitDisturbance();
	void update(double dt) override;
	void render() = 0;
	~AIBirdComponent() override;
};