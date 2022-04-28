#pragma once

#include "../lib_ecm/ecm.h"

class PlayerDataComponent : public Component {
protected:
	int _playerHealth = 100;
	int _reputation = 100;
	int _collisionCount = 0;
	int _timesPoopedOn = 0;

public:
	PlayerDataComponent() = delete;
	explicit PlayerDataComponent(Entity* p, int startingHP, int startingRep) : _playerHealth(startingHP), _reputation(startingRep);
	void TakeDamage(int HP) { _playerHealth -= HP; };
	void Heal(int HP) { _playerHealth += HP; }
	void IncreaseReputation(int Rep) { _reputation += Rep; }
	void DecreaseReputation(int Rep) { _reputation -= Rep; }
	int GetHealth() { return _playerHealth; };
	int GetTimesPoopedOn() { return _timesPoopedOn; };
};