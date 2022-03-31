#include "steering_states.h"
#include "components/cmp_sprite.h"

using namespace sf;

void StationaryState::execute(Entity* owner, double dt) noexcept {
    auto s = owner->get_components<ShapeComponent>();
    s[0]->getShape().setFillColor(Color::Blue);
}

void SeekState::execute(Entity* owner, double dt) noexcept {
    auto s = owner->get_components<ShapeComponent>();
    s[0]->getShape().setFillColor(Color::Green);
    auto output = _steering.getSteering();
    owner->setPosition(owner->getPosition() + (output.direction * (float)dt));
}

void FleeState::execute(Entity* owner, double dt) noexcept {
    auto s = owner->get_components<ShapeComponent>();
    s[0]->getShape().setFillColor(Color::Yellow);
    auto output = _steering.getSteering();
    owner->setPosition(owner->getPosition() + (output.direction * (float)dt));
}