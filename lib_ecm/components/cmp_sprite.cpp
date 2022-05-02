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

FadingTexture::FadingTexture(Entity* p, bool updateToParent) : _sprite(make_shared<sf::Sprite>()), _updateToParent(updateToParent), _fadeIn(false), _fadeOut(false),Component(p) {
    if (_sprite != nullptr) {
        _sprite->setColor(sf::Color(_sprite->getColor().r, _sprite->getColor().g, _sprite->getColor().b, 255));
    }
}

sf::Sprite& FadingTexture::getSprite() const { return *_sprite; }

void FadingTexture::setTexture(std::shared_ptr<sf::Texture> tex)
{
    _texture = tex;
    _sprite->setTexture(*_texture);
}


void FadingTexture::update(double dt) {
    if (_fadeOut) {
        if (_sprite->getColor().a == 0) {
            _sprite->setColor(sf::Color(_sprite->getColor().r, _sprite->getColor().g, _sprite->getColor().b, 255));
        }
        else if (_sprite->getColor().a <= 0) {
            _fadeOut = false;
        }
        _sprite->setColor(sf::Color(_sprite->getColor().r, _sprite->getColor().g, _sprite->getColor().b, _sprite->getColor().a - 1));
    }
    else if (_fadeIn) {
        if (_sprite->getColor().a == 255) {
            _sprite->setColor(sf::Color(_sprite->getColor().r, _sprite->getColor().g, _sprite->getColor().b, 0));
        }
        else if (_sprite->getColor().a <= 0) {
            _fadeIn = false;
        }
        _sprite->setColor(sf::Color(_sprite->getColor().r, _sprite->getColor().g, _sprite->getColor().b, _sprite->getColor().a + 1));
    }
}

void FadingTexture::render() {
    Renderer::queue(_sprite.get());
}

FadingTexture::~FadingTexture() {
    _sprite.reset();
    _texture.reset();
}

AnimatedTexture::AnimatedTexture(Entity* p, bool updateToParent, float fps, std::vector<std::shared_ptr<sf::Texture>> textures) : 
    _sprite(make_shared<sf::Sprite>()), _updateToParent(updateToParent), _fps(fps), frameCount(0), time(0),_textures(textures), Component(p) {
    setTextures(textures);
}

sf::Sprite& AnimatedTexture::getSprite() const { return *_sprite; }

void AnimatedTexture::setTextures(std::vector<std::shared_ptr<sf::Texture>> tex) {
    if (tex.size() > 0) {
        _textures = tex;
        _sprite->setTexture(*tex[0]);
    }
    else {
        return;
    }
    
}

void AnimatedTexture::render() {
    Renderer::queue(_sprite.get());
}

void AnimatedTexture::update(double dt) {
    if (_fps != 0)
    {
        if (time < 1 / _fps) {
            time += dt;
        }
        if (frameCount >= _textures.size()) {
            frameCount = 0;
        }
        if (time >= 1 / _fps) {
            _sprite->setTexture(*_textures[frameCount]);
            time = 0;
            ++frameCount;
        }
    }
    if (_updateToParent) {
        _sprite->setPosition(_parent->getPosition());
        _sprite->setRotation(sf::degrees(_parent->getRotation()));
    }
}

AnimatedTexture::~AnimatedTexture() {
    _sprite.reset();
    for (auto e : _textures) {
        e.reset();
    }
    _textures.clear();
}

RotationTrackingTexture::RotationTrackingTexture(Entity* p, bool updateToParent) : _sprite(make_shared<sf::Sprite>()), _updateToParent(updateToParent), _rot(0), _pointToTrack(sf::Vector2f(0,0)), Component(p) {}

void RotationTrackingTexture::setTexture(std::shared_ptr<sf::Texture> tex) {
    if (tex != nullptr) {
        _texture = tex;
        _sprite->setTexture(*_texture);
    }
}

void RotationTrackingTexture::update(double dt) {
    auto vec = _pointToTrack - _sprite->getPosition();
    vec = vec.normalized();
    auto tan = atan2(vec.y, vec.x);
    auto tan_deg = tan * 180 / (4 * atan(1));
    _sprite->setRotation(sf::degrees(tan_deg - 180));
    if (_updateToParent) {
        _sprite->setPosition(_parent->getPosition());
        _parent->setRotation(tan_deg - 180);
    }
}

void RotationTrackingTexture::render() {
    Renderer::queue(_sprite.get());
}

RotationTrackingTexture::~RotationTrackingTexture() {
    _sprite.reset();
    _texture.reset();
}