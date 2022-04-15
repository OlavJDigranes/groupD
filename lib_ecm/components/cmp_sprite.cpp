#include "cmp_sprite.h"
#include "../engine/system_renderer.h"

using namespace std;


void SpriteComponent::setTexure(std::shared_ptr<sf::Texture> tex)
{
    _texture = tex;
    _sprite->setTexture(*_texture);
}


SpriteComponent::SpriteComponent(Entity* p)
    : Component(p), _sprite(make_shared<sf::Sprite>()) {}

void SpriteComponent::update(double dt) {
    _sprite->setPosition(_parent->getPosition());
    _sprite->setRotation(sf::degrees(_parent->getRotation()));
}

void SpriteComponent::render() { Renderer::queue(_sprite.get()); }

void ShapeComponent::update(double dt) {
    _shape->setPosition(_parent->getPosition());
    if (sf::degrees(_parent->getRotation()) != _rotation) {
        //float diff = _parent->getRotation() - _rotation.asDegrees();
        //_shape->rotate(sf::degrees(diff));
        _shape->setRotation(sf::degrees(_parent->getRotation()));
        _rotation = sf::degrees(_parent->getRotation());
        printf("parent rotation: %f\n", _parent->getRotation());
        printf("sprite rotation: %f\n", _rotation.asDegrees());
    }
}

void ShapeComponent::render() { Renderer::queue(_shape.get()); }

sf::Shape& ShapeComponent::getShape() const { return *_shape; }

ShapeComponent::ShapeComponent(Entity* p)
    : Component(p), _shape(make_shared<sf::CircleShape>()) {}

sf::Sprite& SpriteComponent::getSprite() const { return *_sprite; }
