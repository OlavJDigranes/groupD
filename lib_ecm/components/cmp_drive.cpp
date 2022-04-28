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

AIDrivingComponent::AIDrivingComponent(Entity* parent, const sf::Vector2f size) : Component(parent), 
    _angle(std::make_shared<double>(0)) {
    _driver = std::make_shared<DrivingComponent>(parent, size, "AI");
    _pather = std::make_unique<PathfindingComponent>(parent);
    _sm = std::make_unique<StateMachineComponent>(parent);
    _sm->addState("Accelerating", std::make_shared<AcceleratingState>());
    _sm->addState("Braking", std::make_shared<BrakingState>());
    _sm->addState("TurningLeft", std::make_shared<TurningLeftState>(_angle));
    _sm->addState("TurningRight", std::make_shared<TurningRightState>(_angle));
    _pather->FindNewCheckpoint();
    _path = _pather->getPath();
    _index = _pather->getIndex();
    _analysedPath = std::make_shared<std::vector<PathNode>>();
    AnalysePath();
    lastNode = _analysedPath->at(0);
    printf("Set up path for AI\n");
    _sm->changeState("Accelerating");
}

void AIDrivingComponent::AnalysePath() {
    sf::Vector2i prev_dir;
    for (int i = 0; i < _path->size(); i++) {
        PathNode p;
        sf::Vector2i dir = sf::Vector2i(0,0);
        p.tilePos = sf::Vector2ul(_path->at(i).x, _path->at(i).y);
        p.worldPos = ls::getTilePosition(sf::Vector2ul(_path->at(i).x, _path->at(i).y));
        p.idx = i;
        p.isCorner = false;
        p.turnLeft = false;
        if (i + 1 < _path->size()) {
            dir = _path->at(i + 1) - _path->at(i);
            if (i == 0) {
                prev_dir = dir;
            }
        }
        bool dX = dir.x != prev_dir.x;
        bool dY = dir.y != prev_dir.y;
        if (dX && dY)
        {
            p.isCorner = true;
            if (prev_dir.x == -1 && dir.y == 1) {
                p.turnLeft = true;
            }
            if (prev_dir.x == 1 && dir.y == -1) {
                p.turnLeft = true;
            }
            if (prev_dir.y == 1 && dir.x == 1) {
                p.turnLeft = true;
            }
            if (prev_dir.y == -1 && dir.x == -1) {
                p.turnLeft = true;
            }
        }
        _analysedPath->push_back(p);
        prev_dir = dir;
    }
}

void AIDrivingComponent::ComputeActions(double dt) {
    if (_analysedPath->at(*_index).isCorner) {
        if (_driver->GetCurrentSpeed() > 4) {
            _sm->changeState("Braking");
            return;
        }
    }
    auto dir = *_driver->GetDirection();
    sf::Vector2f nextLoc = _analysedPath->at(*_index).worldPos + sf::Vector2f(ls::getTileSize() / 2, ls::getTileSize() / 2); //sf::Vector2ul(_analysedPath->at(*_index).worldPos.x, _analysedPath->at(*_index).worldPos.y);
    auto trg = nextLoc - _parent->getPosition();
    trg = trg.normalized();

    auto top = (dir.x * trg.x) + (dir.y * trg.y);
    auto bottom = (sqrt(pow(dir.x, 2) + pow(dir.y, 2))) * (sqrt(pow(trg.x, 2) + pow(trg.y, 2)));
    auto sum = top / bottom;
    *_angle = sf::rad2deg(acos(sum));
    if (std::isnan(*_angle)) {
       *_angle = 0;
    }
    else {
        //if facing right
        if (dir.x > dir.y && dir.x > 0) {
            if (nextLoc.y < _parent->getPosition().y) {
                _sm->changeState("TurningLeft");
                return;
            }
            else {
                _sm->changeState("TurningRight");
                return;
            }
        }
        else if (dir.x < dir.y && dir.x < 0) {
            if (nextLoc.y > _parent->getPosition().y) {
                _sm->changeState("TurningLeft");
                return;
            }
            else {
                _sm->changeState("TurningRight");
                return;
            }
        }
        // if facing down
        else if (dir.y > dir.x && dir.y > 0) {
            if (nextLoc.x > _parent->getPosition().x) {
                _sm->changeState("TurningLeft");
                return;
            }
            else {
                _sm->changeState("TurningRight");
                return;
            }
        }
        // if facing up
        else if (dir.y < dir.x && dir.y < 0) {
            if (nextLoc.x < _parent->getPosition().x) {
                //angle = -angle;
                _sm->changeState("TurningLeft");
                return;
            }
            else {
                _sm->changeState("TurningRight");
                return;
            }
        }

    }
   
    if (_parent->getPosition() != _analysedPath->at(*_index).worldPos) {
        _sm->changeState("Accelerating");
        return;
    }
}

void AIDrivingComponent::update(double dt) {
    if (_path->size() != 0 && *_index < _path->size()) {
        if (lastNode.idx < *_index - 1 && *_index != 0) {
            lastNode = _analysedPath->at(*_index - 1);
        }
        ComputeActions(dt);
        _driver->update(dt);
        _pather->update(dt);
    }
    else {
        _pather->FindNewCheckpoint();
        return;
    }
    _sm->update(dt);
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