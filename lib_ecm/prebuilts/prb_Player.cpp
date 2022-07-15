// Prebuilt Player
#include "prb_Player.h"

Player::Player(Scene* s, sf::Vector2f size, float TopSpeed) : Entity(s) {
	driver = addComponent<DrivingComponent>(size, "Player", TopSpeed);
	controller = addComponent<PlayerController>(driver);
	data = addComponent<PlayerDataComponent>(5, 5, nullptr, nullptr);
}

Player::~Player() {
	driver = nullptr;
	controller = nullptr;
	data = nullptr;
}

void Player::SetPlayerTexture(std::shared_ptr<sf::Texture> tx) {
	sprite->setTexture(tx);
}

void Player::SetHealthTexture(std::shared_ptr<SpriteComponent> tx) {
	data->SetHealthTexture(tx);
}

void Player::SetRepTexture(std::shared_ptr<SpriteComponent> tx) {
	data->SetRepTexture(tx);
}
