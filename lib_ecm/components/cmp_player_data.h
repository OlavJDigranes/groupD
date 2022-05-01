#pragma once

#include "../lib_ecm/ecm.h"
#include "../components/cmp_sprite.h"
#include "engine.h"
#include <SFML/Audio.hpp>

class PlayerDataComponent : public Component {
protected:
	int _hp = 100;
	int _rep = 100;
	int _collisionCount = 0;
	int _timesPoopedOn = 0;
	std::shared_ptr<SpriteComponent> _hpTexture;
	sf::SoundBuffer damageBuffer;
	sf::Sound damage; 

public:
	PlayerDataComponent() = delete;
	explicit PlayerDataComponent(Entity* p, int startingHP, int startingRep, std::shared_ptr<sf::Texture> hpTexture);
	void TakeDamage(int HP) { _hp -= HP; damage.play(); };
	void Heal(int HP) { _hp += HP; }
	void IncreaseReputation(int Rep) { _rep += Rep; }
	void DecreaseReputation(int Rep) { _rep -= Rep; }
	int GetHealth() { return _hp; };
	int getReputation() { return _rep; }
	int GetTimesPoopedOn() { return _timesPoopedOn; };
	void update(double dt) override;
	void render() override;
	//~PlayerDataComponent() {};
};