#pragma once

#include "cmp_sprite.h"
#include "../lib_ecm/ecm.h"
#include <Box2D/Box2D.h>
#include "Box2D/Dynamics/b2Body.h"

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
