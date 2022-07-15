#pragma once
#include "ecm.h"
#include "components/cmp_drive.h"
#include "components/cmp_player_controller.h"
#include "components/cmp_player_data.h"
#include "components/cmp_sprite.h"

class Player : public Entity {
public:
	Player(Scene* scene, sf::Vector2f size, float TopSpeed);
	~Player() override;

	void SetPlayerTexture(std::shared_ptr<sf::Texture> tx);
	void SetHealthTexture(std::shared_ptr<SpriteComponent> tx);
	void SetRepTexture(std::shared_ptr<SpriteComponent> tx);

protected:

private:
	std::shared_ptr<DrivingComponent> driver{ nullptr };
	std::shared_ptr<PlayerController> controller{ nullptr };
	std::shared_ptr<PlayerDataComponent> data{ nullptr };
	std::shared_ptr<SpriteComponent> sprite{ nullptr };
};