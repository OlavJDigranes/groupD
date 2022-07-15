// Prebuilt Player
#include "prb_Player.h"

Player::Player(Scene* s, sf::Vector2f size, float TopSpeed) : Entity(s) {
	driver = std::make_shared<DrivingComponent>(this, size, "Player", TopSpeed);
	controller = std::make_unique<PlayerController>(this, driver);
	data = std::make_unique<PlayerDataComponent>(this, 5, 5, nullptr, nullptr);
}

Player::~Player() {
	driver = nullptr;
	controller = nullptr;
	data = nullptr;
}

void Player::update(double dt) {
	driver->update(dt);
	controller->update(dt);
	data->update(dt);
	sprite->update(dt);
}

void Player::render() {
	sprite->render();
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
