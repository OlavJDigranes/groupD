#pragma once

#include "../lib_ecm/ecm.h"
#include "../components/cmp_sprite.h"
#include "engine.h"
#include <SFML/Audio.hpp>

class PlayerDataComponent : public Component {
protected:
	int startingHP;
	int _hp = 100;
	int startingRep;
	int _rep = 100;
	int _repDecreases = 0;
	int _hpDecreases = 0;
	std::shared_ptr<SpriteComponent> _hpTexture;
	std::shared_ptr<SpriteComponent> _repTexture;
	sf::Vector2i hpSize, hpPos;
	sf::Vector2i repSize, repPos;
	sf::SoundBuffer damageBuffer;
	sf::Sound damage; 
	int hpAdj;
	int repAdj;

public:
	PlayerDataComponent() = delete;
	explicit PlayerDataComponent(Entity* p, int startingHP, int startingRep, std::shared_ptr<sf::Texture> hpTexture, std::shared_ptr<sf::Texture> repTexture);
	~PlayerDataComponent();
	
	void update(double dt) override;
	void render() override;
	
	void SetHealthTexture(std::shared_ptr<SpriteComponent> tx) { _hpTexture = tx; };
	void SetRepTexture(std::shared_ptr<SpriteComponent> tx) { _repTexture = tx; };

	void TakeDamage(int HP);
	void Heal(int HP);
	void IncreaseReputation(int Rep);
	void DecreaseReputation(int Rep);
	int GetHealth() { return _hp; };
	int GetReputation() { return _rep; }
	int GetTimesPoopedOn() { return _hpDecreases; };
};