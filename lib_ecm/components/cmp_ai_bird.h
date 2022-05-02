#pragma once
#include "../lib_ecm/ecm.h"
#include "cmp_ai_steering.h"
#include "cmp_state_machine.h"
#include "cmp_player_data.h"
#include "cmp_sprite.h"
#include "states_bird.h"
#include "maths.h"
#include <LevelSystem.h>
#include <SFML/Audio.hpp>

class AIBirdComponent : public Component {
protected:
	std::shared_ptr<BirdSteering> _str;
	std::unique_ptr<StateMachineComponent> _sm;
	std::shared_ptr<Entity> _player;
	std::shared_ptr<AnimatedTexture> _tex;
	b2Body* _body;
	b2Fixture* _fixture;
	bodyUserData* _data;
	std::vector<const b2Contact const*> _dirtyCheck;
	bool _isChasing = false;
	sf::Vector2f homeLoc;
	bool _overPlayer = false;
	double _timeToPoop = 0;
	int randNum; 

	//Sounds
	sf::SoundBuffer splatBuffer;
	sf::Sound splat; 

	sf::SoundBuffer flyingBuffer1;
	sf::Sound flying1;
	sf::SoundBuffer flyingBuffer2;
	sf::Sound flying2;
	sf::SoundBuffer flyingBuffer3;
	sf::Sound flying3;

	sf::SoundBuffer birdQueBuffer;
	sf::Sound birdQue; 

public:
	void CheckForPlayer(double dt);
	void SetChasing(bool isChasing) { _isChasing = isChasing; }
	std::shared_ptr<BirdSteering> GetSteeringComponent() { return _str; }
	const sf::Vector2f GetHomeLocation() { return homeLoc; }
	const bool IsOverPlayer() { return _overPlayer; };
	std::shared_ptr<Entity> getPlayer() { return _player; }
	void setAnimationCmp(std::shared_ptr<AnimatedTexture> tex) { _tex = tex; };
	
	void update(double dt) override;
	void render() override;
	
	AIBirdComponent() = delete;
	explicit AIBirdComponent(Entity* p, std::shared_ptr<Entity> player, sf::Vector2i levelBounds, sf::Vector2f size);
	~AIBirdComponent();
};