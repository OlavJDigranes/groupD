#include "cmp_player_data.h"

PlayerDataComponent::PlayerDataComponent(Entity* p, int startingHP, int startingRep, std::shared_ptr<sf::Texture> hpTexture) : _hp(startingHP), _rep(startingRep), Component(p) {
	_hpTexture = std::make_shared<SpriteComponent>(p, false);
	_hpTexture->setTexture(hpTexture);
}

void PlayerDataComponent::update(double dt) {
	_hpTexture->getSprite().setPosition(Engine::GetWindow().getView().getCenter() + sf::Vector2f(0.425 * Engine::getWindowSize().x, -0.425 * Engine::getWindowSize().y));
	_hpTexture->getSprite().setColor(sf::Color(255, 255, 255, 255));
}

void PlayerDataComponent::render() {
	_hpTexture->render();
}