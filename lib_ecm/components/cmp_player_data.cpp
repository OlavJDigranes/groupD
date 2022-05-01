#include "cmp_player_data.h"

PlayerDataComponent::PlayerDataComponent(Entity* p, int startingHP, int startingRep, std::shared_ptr<sf::Texture> hpTexture) : _hp(startingHP), _rep(startingRep), Component(p) {
	_hpTexture = std::make_shared<SpriteComponent>(p, false);
	_hpTexture->setTexture(hpTexture);
	damageBuffer.loadFromFile("res/music/LifeLoss.mp3");
	damage.setBuffer(damageBuffer); 
	damage.setVolume(60); 
}

void PlayerDataComponent::update(double dt) {
	_hpTexture->getSprite().setPosition(Engine::GetWindow().getView().getCenter() + sf::Vector2f(0.425 * Engine::getWindowSize().x, -0.425 * Engine::getWindowSize().y));
	int alpha = 255 - (_hp / 100 * 51);
	_hp < 100 ? _hpTexture->getSprite().setColor(sf::Color(255, 255, 255, alpha)) : _hpTexture->getSprite().setColor(sf::Color(255, 255, 255, 255));
}

void PlayerDataComponent::render() {
	_hpTexture->render();
}

PlayerDataComponent::~PlayerDataComponent() {
	_hpTexture = nullptr;
}