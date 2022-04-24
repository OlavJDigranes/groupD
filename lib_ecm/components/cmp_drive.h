#pragma once

#include "../lib_ecm/ecm.h"
#include "components/cmp_path_follow.h"
#include "Box2D/Dynamics/b2Body.h"
#include "system_physics.h"
#include "components/cmp_sprite.h"
#include <LevelSystem.h>
#include <maths.h>

#define DEBUG_TELEPORT

class DrivingComponent : public Component {
protected:
	Entity* _parent;
	b2Body* _body;
	float32 _currentSpeed;
	b2Vec2 _size;
	b2Vec2 _halfSize;
	std::shared_ptr<b2Vec2> _direction;
	bodyUserData* _data;

public:
	void Drive(float speed, double dt);
	void Brake(double dt);
	void Rotate(float degrees, float dt);
	std::shared_ptr<b2Vec2> GetDirection() { return _direction; }
	void SetDirection(b2Vec2 newDir) { *_direction = newDir; };
	void SetDirection(sf::Vector2i newDir) { SetDirection(b2Vec2(newDir.x, newDir.y)); };
	float32 GetCurrentSpeed() { return _currentSpeed; }

	void render() override {};
	void update(double dt) override;

	explicit DrivingComponent(Entity* parent, sf::Vector2f size, const char data[]);
	DrivingComponent() = delete;
	~DrivingComponent();
#ifdef DEBUG_TELEPORT
	void teleport(sf::Vector2f pos);
#endif
};

class AIDrivingComponent : public Component {
#define DEBUG_AI_PATH
protected:
	struct PathNode {
		sf::Vector2ul tilePos;
		sf::Vector2f worldPos;
		int idx;
		bool isCorner;
		bool turnLeft;
	};

	std::vector<SpriteComponent> debug;

	int _actions;
	std::unique_ptr<DrivingComponent> _driver;
	std::unique_ptr<PathfindingComponent> _pather;
	std::shared_ptr<std::vector<sf::Vector2i>> _path;
	std::shared_ptr<size_t> _index;
	std::shared_ptr<std::vector<PathNode>> _analysedPath;
	PathNode lastNode;
	void AnalysePath();
	void ComputeActions(double dt);
public:
	void render() override {};
	void update(double dt) override;

	std::shared_ptr<std::vector<PathNode>> getPath() { return _analysedPath; };

	AIDrivingComponent() = delete;
	explicit AIDrivingComponent(Entity* parent, sf::Vector2f size);
	~AIDrivingComponent();
};