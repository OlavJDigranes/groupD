#pragma once

#include "cmp_sprite.h"
#include "cmp_ai_bird.h"
#include "../lib_ecm/ecm.h"
#include <Box2D/Box2D.h>
#include "Box2D/Dynamics/b2Body.h"
#include <LevelSystem.h>

//#define DEBUG_GRATE_TRIGGER_RADIUS

class PhysicsComponent : public Component {
protected:
  b2Body* _body;
  bodyUserData* _data;
  const bool _dynamic;
  b2Fixture* _fixture;

public:
  PhysicsComponent(Entity* p, bool dyn, const sf::Vector2f& size);

  b2Fixture* const getFixture() const;
  bool isTouching(const PhysicsComponent& pc) const;
  bool isTouching(const PhysicsComponent& pc, b2Contact const* bc) const;
  std::vector<const b2Contact*> getTouching() const;
  const sf::Vector2f getVelocity() const;
  void setRestitution(float r);
  void setFriction(float r);
  void setMass(float m);
  void update(double dt) override;
  void render() override;
  void impulse(const sf::Vector2f& i);
  void dampen(const sf::Vector2f& s);
  void setVelocity(const sf::Vector2f& v);
  void teleport(const sf::Vector2f& v);
  ~PhysicsComponent() override;
};

class PhysicsTriggerComponent : public Component {
protected:
	b2Body* _body;
	bodyUserData* _data;
	const bool _dynamic;
	b2Fixture* _fixture;
	std::vector<const b2Contact const*> _dirtyCheck;
	bool _isGoal;
	bool _isActive;
	bool goalReached;
	bool _playerOverlap;
public:
	PhysicsTriggerComponent(Entity* p, const sf::Vector2f& size, bool isGoal, bool isActive);
	void IsPlayerOverlapping();
	bool HasGoalBeenReached();
	bool IsActive();
	void SetActive(bool active);
	void update(double dt) override;
	void render() override;
	~PhysicsTriggerComponent() override;
};

//class GrateComponent : public PhysicsTriggerComponent {
//protected:
//	b2Fixture* _trigger;
//	std::vector<const b2Contact const*> _triggerDirtyCheck;
//	bool _isExpanding;
//public:
//	GrateComponent() = delete;
//	explicit GrateComponent(Entity* p, const sf::Vector2f& size);
//	void ExpandAndNotify(double dt);
//	void ResetSize(double dt);
//	float32 ReturnTriggerRadius() { return _trigger->GetShape()->m_radius; };
//	void update(double dt) override;
//	~GrateComponent() override;
//#ifdef DEBUG_GRATE_TRIGGER_RADIUS
//	void ConsumeDebugCmp(std::shared_ptr<ShapeComponent> cmp);
//	std::shared_ptr<ShapeComponent> debug;
//#endif
//};

class GrateComponent : public PhysicsTriggerComponent {
protected:
	std::vector<std::shared_ptr<Entity>> _birds;
	bool _toReset;
public:
	GrateComponent() = delete;
	explicit GrateComponent(Entity* p, const sf::Vector2f& size, std::vector<std::shared_ptr<Entity>> birds)
		: PhysicsTriggerComponent(p, size, false, true), _birds(birds), _toReset(false) {};
	void update(double dt) override;
	void render() override {};
	~GrateComponent();
};
