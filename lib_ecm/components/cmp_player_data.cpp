#include "cmp_player_data.h"

PlayerDataComponent::PlayerDataComponent(Entity* p, int HP, int Rep, std::shared_ptr<sf::Texture> hpTexture, std::shared_ptr<sf::Texture> repTexture) : _hp(HP), _rep(Rep), startingHP(HP), startingRep(Rep), Component(p) {
	_hpTexture = std::make_shared<SpriteComponent>(p, false);
	_repTexture = std::make_shared<SpriteComponent>(p, false);
	_hpTexture->setTexture(hpTexture);
	_repTexture->setTexture(repTexture);
	damageBuffer.loadFromFile("res/music/LifeLoss.mp3");
	damage.setBuffer(damageBuffer); 
	damage.setVolume(60); 
	hpPos = _hpTexture->getSprite().getTextureRect().getPosition();
	hpSize = _hpTexture->getSprite().getTextureRect().getSize();
	repPos = _repTexture->getSprite().getTextureRect().getPosition();
	repSize = _repTexture->getSprite().getTextureRect().getSize();
	hpAdj = hpSize.y / 5;
	repAdj = repSize.y / 5;
}

void PlayerDataComponent::TakeDamage(int HP) {
	damage.play();
	_hp -= HP;
	++_hpDecreases;
	_hpTexture->getSprite().setTextureRect(sf::IntRect(hpPos, sf::Vector2i(hpSize.x, hpSize.y - hpAdj * _hpDecreases)));
}

void PlayerDataComponent::Heal(int HP) {
	_hp += HP;
}

void PlayerDataComponent::IncreaseReputation(int Rep) {
	_rep += Rep;
}

void PlayerDataComponent::DecreaseReputation(int Rep) {
	_rep -= Rep;
	++_repDecreases;
	_repTexture->getSprite().setTextureRect(sf::IntRect(repPos, sf::Vector2i(repSize.x, repAdj * _repDecreases)));
}

void PlayerDataComponent::update(double dt) {
	_hpTexture->getSprite().setPosition(Engine::GetWindow().getView().getCenter() + sf::Vector2f(0.425 * Engine::getWindowSize().x, -0.425 * Engine::getWindowSize().y));
	_repTexture->getSprite().setPosition(Engine::GetWindow().getView().getCenter() + sf::Vector2f(0.375 * Engine::getWindowSize().x, -0.425 * Engine::getWindowSize().y));
}

void PlayerDataComponent::render() {
	_hpTexture->render();
	_repTexture->render();
}

PlayerDataComponent::~PlayerDataComponent() {
	_hpTexture = nullptr;
	_repTexture = nullptr;
}