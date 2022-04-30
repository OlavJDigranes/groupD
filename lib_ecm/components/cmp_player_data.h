#pragma once

#include "../lib_ecm/ecm.h"

class PlayerDataComponent : public Component {
protected:
	int _hp = 100;
	int _rep = 100;
	int _collisionCount = 0;
	int _timesPoopedOn = 0;

public:
	PlayerDataComponent() = delete;
	explicit PlayerDataComponent(Entity* p, int startingHP, int startingRep) : _hp(startingHP), _rep(startingRep), Component(p) {};
	void TakeDamage(int HP) { _hp -= HP; };
	void Heal(int HP) { _hp += HP; }
	void IncreaseReputation(int Rep) { _rep += Rep; }
	void DecreaseReputation(int Rep) { _rep -= Rep; }
	int GetHealth() { return _hp; };
	int getReputation() { return _rep; }
	int GetTimesPoopedOn() { return _timesPoopedOn; };
	void update(double dt) override {};
	void render() override {};
	//~PlayerDataComponent() {};
};