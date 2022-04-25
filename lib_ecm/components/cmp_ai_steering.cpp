//"cmp_ai_steering.cpp"
#include "cmp_ai_steering.h"

using namespace sf;

void SteeringComponent::update(double dt) {
    if (_isActive)
    {
        auto rot = _face.getSteering();
        rotate(rot, dt);
        if (_parent->getPosition() != _targetLoc) {
            auto output = _seek.getSteering();
            move(output.direction * (float)dt, rot.rotation * (float)dt);
        }
        else if (!_atTarget) {
            auto output = _flee.getSteering();
            move(output.direction * (float)dt, rot.rotation * (float)dt);
            _atTarget = true;
        }
        //auto rot = _face.getSteering();
        //rotate(rot, dt);
        //// If target (player) is more than 100 pixels away seek 
        //if (length(_parent->getPosition() - _player->getPosition()) > 100.0f) {
        //    auto output = _seek.getSteering();
        //    move(output.direction * (float)dt, rot.rotation * (float)dt);
        //}
        //// If target (player) is less than 50 pixels away flee
        //else if (length(_parent->getPosition() - _player->getPosition()) <
        //    50.0f) {
        //    auto output = _flee.getSteering();
        //    move(output.direction * (float)dt, rot.rotation * (float)dt);
        //}
    }
}

SteeringComponent::SteeringComponent(Entity* p, Entity* player, bool ActiveOnCreation, Vector2i mapBounds)
    : _player(player), _isActive(ActiveOnCreation), _mapBounds(mapBounds),_seek(Seek(p, player, 100.0f)),
    _flee(Flee(p, player, 100.0f)), _face(Face(p, player, 100.0f)), Component(p) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = Physics::sv2_to_bv2(_parent->getPosition());
    _body = Physics::GetWorld()->CreateBody(&bodyDef);
    _body->SetActive(true);
    _body->SetLinearDamping(0.5);
}

bool SteeringComponent::validMove(const sf::Vector2f& pos) const {
    if (pos.x < 0.0f || pos.x > _mapBounds.x ||
        pos.y < 0.0f || pos.y > _mapBounds.y) {
        return false;
    }
    return true;
}

void SteeringComponent::move(const sf::Vector2f& p, float f) {
    auto new_pos = _parent->getPosition() + p;
    if (validMove(new_pos)) {
        _parent->setPosition(new_pos);
    }
}

void SteeringComponent::move(float x, float y, float f) { move(Vector2f(x, y), f); }

void SteeringComponent::rotate(SteeringOutput steer, float dt) {
    steer.direction = steer.direction.rotatedBy(sf::degrees(steer.rotation * dt));
    if (_body->GetAngle() > 4 * atan(1)) {
        _body->SetTransform(_body->GetPosition(), -4 * atan(1));
    }
    _body->SetTransform(_body->GetPosition(), _body->GetAngle() + sf::deg2rad(steer.rotation * dt));
    _parent->setRotation(_parent->getRotation() + (steer.rotation * dt));
}

bool SteeringComponent::IsActive() {
    return _isActive;
}

void SteeringComponent::SetActive(bool Active) {
    _isActive = Active;
}

/*
void SteeringComponent::update(double dt) {
    // If target (player) is more than 100 pixels away seek
    if (length(_parent->getPosition() - _player->getPosition()) > 100.0f) {
        auto output = _seek.getSteering();
        move(output.direction * (float)dt);
    }
    // If target (player) is less than 50 pixels away flee
    else if (length(_parent->getPosition() - _player->getPosition()) <
        50.0f) {
        auto output = _flee.getSteering();
        move(output.direction * (float)dt);
    }
}

SteeringComponent::SteeringComponent(Entity* p, Entity* player)
    : _player(player), _seek(Seek(p, player, 100.0f)),
    _flee(Flee(p, player, 100.0f)), Component(p) {}

bool SteeringComponent::validMove(const sf::Vector2f& pos) const {
    if (pos.x < 0.0f || pos.x > Engine::GetWindow().getSize().x ||
        pos.y < 0.0f || pos.y > Engine::GetWindow().getSize().y) {
        return false;
    }
    return true;
}

void SteeringComponent::move(const sf::Vector2f& p) {
    auto new_pos = _parent->getPosition() + p;
    if (validMove(new_pos)) {
        _parent->setPosition(new_pos);
    }
}

void SteeringComponent::move(float x, float y) { move(Vector2f(x, y)); }
*/