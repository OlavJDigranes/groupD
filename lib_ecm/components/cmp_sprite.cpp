#include "cmp_sprite.h"
#include "../engine/system_renderer.h"

using namespace std;


void SpriteComponent::setTexture(std::shared_ptr<sf::Texture> tex)
{
    _texture = tex;
    _sprite->setTexture(*_texture);
}


SpriteComponent::SpriteComponent(Entity* p, bool updateToParent)
    : Component(p), _sprite(make_shared<sf::Sprite>()), _updateToParent(updateToParent) {}

void SpriteComponent::update(double dt) {
    if (_updateToParent) {
        _sprite->setPosition(_parent->getPosition());
        _sprite->setRotation(sf::degrees(_parent->getRotation()));
    }
}

void SpriteComponent::render() { Renderer::queue(_sprite.get()); }

void ShapeComponent::update(double dt) {
    _shape->setPosition(_parent->getPosition());
    if (sf::degrees(_parent->getRotation()) != _rotation) {
        _shape->setRotation(sf::degrees(_parent->getRotation()));
        _rotation = sf::degrees(_parent->getRotation());
    }
}

void ShapeComponent::render() { Renderer::queue(_shape.get()); }

sf::Shape& ShapeComponent::getShape() const { return *_shape; }

ShapeComponent::ShapeComponent(Entity* p)
    : Component(p), _shape(make_shared<sf::CircleShape>()) {}

sf::Sprite& SpriteComponent::getSprite() const { return *_sprite; }
