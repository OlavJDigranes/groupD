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
	std::shared_ptr<RotationTrackingTexture> _arrowTex;
	sf::Vector2i hpSize, hpPos;
	sf::Vector2i repSize, repPos;
	sf::Vector2f _currentGoal;
	sf::SoundBuffer damageBuffer;
	sf::Sound damage; 
	int hpAdj;
	int repAdj;

public:
	PlayerDataComponent() = delete;
	explicit PlayerDataComponent(Entity* p, int startingHP, int startingRep, sf::Vector2f currentGoal, std::shared_ptr<sf::Texture> hpTexture, std::shared_ptr<sf::Texture> repTexture, std::shared_ptr<sf::Texture> arrowTex);
	void TakeDamage(int HP) { _hp -= HP; damage.play(); ++_hpDecreases; };
	void Heal(int HP) { _hp += HP; }
	void IncreaseReputation(int Rep) { _rep += Rep; }
	void DecreaseReputation(int Rep) { _rep -= Rep; ++_repDecreases; }
	int GetHealth() { return _hp; };
	int getReputation() { return _rep; }
	int GetTimesPoopedOn() { return _hpDecreases; };
	sf::Vector2f GetCurrentGoalPoint() { return _currentGoal; };
	void SetGoalPoint(sf::Vector2f point) { _currentGoal = point; _arrowTex->SetPointToTrack(point); }
	void update(double dt) override;
	void render() override;
	~PlayerDataComponent();
};