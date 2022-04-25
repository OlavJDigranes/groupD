#include "cmp_drive.h"

DrivingComponent::DrivingComponent(Entity* parent, const sf::Vector2f size, const char data[]) : Component(parent) {
	_parent = parent;
    _direction = std::make_shared<b2Vec2>(b2Vec2(0, -1));
    _currentSpeed = 0;
    _size = Physics::sv2_to_bv2(size, true);
    _halfSize = Physics::sv2_to_bv2(0.5f * size);

    _data = new bodyUserData();
    _data->_parent = parent;
    _data->_tag = data;

    // Body definition and assignment to parent
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = Physics::sv2_to_bv2(_parent->getPosition());
    _body = Physics::GetWorld()->CreateBody(&bodyDef);
	_body->SetGravityScale(0);
    _body->SetTransform(Physics::sv2_to_bv2(_parent->getPosition()), sf::deg2rad(_parent->getRotation()));
    _body->SetActive(true);
    _body->SetLinearDamping(0.5);
    _body->SetAngularDamping(1);
    _body->SetFixedRotation(false);
    _body->SetUserData(_data);

    //Fixture definition and assignment to body
    b2FixtureDef fixDef;
    b2PolygonShape box;
    box.SetAsBox(_halfSize.x, _halfSize.y, b2Vec2_zero, _body->GetAngle());
    fixDef.shape = &box;
    fixDef.density = 1;
    _body->CreateFixture(&fixDef);
}

void DrivingComponent::Drive(float speed, double dt) {
    // If brakes have been activated then reset damping
    if (_body->GetLinearDamping() > 0.5) {
        _body->SetLinearDamping(0.5);
    }
    // If below top speed, set body velocity to increase in direction and let parent (sprite) update
    if (_body->GetLinearVelocity().LengthSquared() <= pow(8, 2) && _body->GetLinearVelocity().LengthSquared() >= 0 && _currentSpeed <= 8) {
        _body->SetLinearVelocity(b2Vec2((_currentSpeed + (speed * dt)) * *_direction));
        _parent->setPosition(Physics::bv2_to_sv2(_body->GetPosition()));
        _currentSpeed += speed * dt;
    }
}

void DrivingComponent::Brake(double dt) {
    // Increase damping if car is moving
    auto damping = _body->GetLinearDamping();
    if (damping >= 0.5 && damping < 3) {
        _body->SetLinearDamping(damping + dt);
    }
}

void DrivingComponent::Rotate(float degrees, float dt) {
    // Rotate parent and update body to match
    *_direction = Physics::sv2_to_bv2(Physics::bv2_to_sv2(*_direction).rotatedBy(sf::degrees(degrees * dt)));
    _direction->Normalize();
    auto forceLoc = _body->GetWorldPoint(b2Vec2(*_direction));
    _parent->setRotation(_parent->getRotation() + (degrees * dt));
    _body->SetTransform(_body->GetPosition(), sf::deg2rad(_parent->getRotation()));
}

void DrivingComponent::update(double dt) {
    if (_body->GetLinearDamping() > 0.5 || _currentSpeed == 0) {
        _body->SetLinearDamping(0.5);   // if car is stationary or not braking then reduce damping
    }
    _body->SetLinearVelocity(_body->GetLinearVelocity().Length() * *_direction); // ensure the car is always travelling forwards when turning with no accel
    _currentSpeed = _body->GetLinearVelocity().Length(); // Update speed to follow damping effects
    _parent->setPosition(Physics::bv2_to_sv2(_body->GetPosition())); // Set parent to follow body when not moving
}

DrivingComponent::~DrivingComponent() {
    _body->SetActive(false);
    _data = nullptr;
    Physics::GetWorld()->DestroyBody(_body);
    // delete _body;
    _body = nullptr;
}

#ifdef DEBUG_TELEPORT
void DrivingComponent::teleport(sf::Vector2f pos) {
    _body->SetTransform(Physics::sv2_to_bv2(pos), sf::deg2rad(_parent->getRotation()));
}
#endif

AIDrivingComponent::AIDrivingComponent(Entity* parent, const sf::Vector2f size) : Component(parent) {
    _driver = std::make_unique<DrivingComponent>(parent, size, "AI");
    _pather = std::make_unique<PathfindingComponent>(parent);
    _pather->FindNewCheckpoint();
    _path = _pather->getPath();
    _index = _pather->getIndex();
    AnalysePath();
    lastNode = _analysedPath.at(0);
    printf("Set up path for AI\n");
}

void AIDrivingComponent::AnalysePath() {
    for (int i = 0; i < _path->size(); i++) {
        PathNode p;
        sf::Vector2i dir = sf::Vector2i(0,0);
        p.pos = ls::getTilePosition(sf::Vector2ul(_path->at(i).x, _path->at(i).y));
        p.idx = i;
        p.isCorner = false;
        p.turnLeft = false;
        if (i + 2 < _path->size()) {
            dir = _path->at(i + 2) - _path->at(i);
        }
        if (dir.x != 0 && dir.y != 0)
        {
            p.isCorner = true;
            if (dir.y > 0) {
                if (dir.x < 0) {
                    p.turnLeft = true;
                }
            }
            else {
                if (dir.x > 0) {
                    p.turnLeft = true;
                }
            }
        }
        /*auto horizontalDiff = _path->at(i + 2).x != _path->at(i).x;
        auto verticalDiff = _path->at(i + 2).y != _path->at(i).y;
        if (horizontalDiff && verticalDiff) {
            p.isCorner = true;
            if (p.pos.x < _path->at(*_index + 2).x) {
                if (p.pos.y < _path->at(*_index + 2).y) {
                    p.turnLeft = true;
                }
            }
            else {
                if (p.pos.x > _path->at(*_index + 2).x) {
                    if (p.pos.y > _path->at(*_index + 2).y) {
                        p.turnLeft = true;
                    }
                }
            }
        }*/
        _analysedPath.push_back(p);
    }
}

void AIDrivingComponent::ComputeActions(double dt) {
    bool braking = false;
    //printf("Current Position = %f, %f\n", _parent->getPosition().x, _parent->getPosition().y);
    //printf("Target = %f, %f\n", _analysedPath.at(*_index).pos.x, _analysedPath.at(*_index).pos.y);
    //printf("Target index = %f\n", *_index);
    //system("cls");
    if (_analysedPath.at(*_index).isCorner) {
        if (_driver->GetCurrentSpeed() > 1) {
            _driver->Brake(dt);
            braking = true;
        }
    }
    auto dir = *_driver->GetDirection();
    sf::Vector2ul nextLoc = sf::Vector2ul(_analysedPath.at(*_index).pos.x, _analysedPath.at(*_index).pos.y);
    auto trg = Physics::sv2_to_bv2(sf::Vector2f(nextLoc + sf::Vector2ul(ls::getTileSize()/2, ls::getTileSize() / 2)) - _parent->getPosition());
    trg.Normalize();

    if (dir.x > trg.x + 0.025 || dir.y > trg.y + 0.025) {
        float adj_rate;
        dir.x > trg.x + 0.025 ? adj_rate = dir.x - trg.x : adj_rate = dir.y - trg.y;
        _driver->Rotate(-180 * (1 + adj_rate), dt);
        if (_driver->GetCurrentSpeed() > 1) {
            _driver->Brake(dt);
            braking = true;
        }
    }
    if (dir.x < trg.x - 0.025 || dir.y < trg.y - 0.025) {
        float adj_rate;
        dir.x < trg.x + 0.025 ? adj_rate = trg.x - dir.x : adj_rate = trg.y - dir.y;
        _driver->Rotate(180 * (1 + adj_rate), dt);
        if (_driver->GetCurrentSpeed() > 1) {
            _driver->Brake(dt);
            braking = true;
        }
    }
   
    if (!braking && _parent->getPosition() != _analysedPath.at(*_index).pos) {
        _driver->Drive(0.1, dt);
    }
}

void AIDrivingComponent::update(double dt) {
    if (_path->size() != 0) {
        if (lastNode.idx < *_index - 1 && *_index != 0) {
            lastNode = _analysedPath.at(*_index - 1);
        }
        ComputeActions(dt);
        //_driver->Drive(1, dt);
        _driver->update(dt);
        _pather->update(dt);
    }
    else {
        _pather->FindNewCheckpoint();
        return;
    }
    //Component::update(dt);
}

AIDrivingComponent::~AIDrivingComponent() {
    _driver->~DrivingComponent();
    _pather->~PathfindingComponent();
    _driver = nullptr;
    _pather = nullptr;
    _path = nullptr;
    _index = nullptr;
    Component::~Component();
}