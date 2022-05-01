#pragma once

#include "../lib_ecm/ecm.h"
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>

class SpriteComponent : public Component {
protected:
    std::shared_ptr<sf::Sprite> _sprite;
    std::shared_ptr<sf::Texture> _texture;
    bool _updateToParent;
public:
    SpriteComponent() = delete;

    explicit SpriteComponent(Entity* p, bool updateToParent);
    void update(double dt) override;
    void render() override;

    sf::Sprite& getSprite() const;


    void setTexture(std::shared_ptr<sf::Texture> tex);
};

class ShapeComponent : public Component {
protected:
    std::shared_ptr<sf::Shape> _shape;
    sf::Angle _rotation;

public:
    ShapeComponent() = delete;

    explicit ShapeComponent(Entity* p);

    void update(double dt) override;
    void render() override;
    sf::Shape& getShape() const;
    template <typename T, typename... Targs> void setShape(Targs... params) {
        _shape.reset(new T(params...));
    }
};

class FadingTexture : public Component {
protected:
    std::shared_ptr<sf::Sprite> _sprite;
    std::shared_ptr<sf::Texture> _texture;
    bool _updateToParent;
    bool _fadeOut;
    bool _fadeIn;

public:
    FadingTexture() = delete;
    explicit FadingTexture(Entity* p, bool updateToParent);
    void setTexture(std::shared_ptr<sf::Texture> tex);
    sf::Sprite& getSprite() const;
    void SetFadeOut(bool fadeOut) { _fadeOut = fadeOut; };
    void SetFadeIn(bool fadeIn) { _fadeIn = fadeIn; };
    void update(double dt) override;
    void render() override;
};