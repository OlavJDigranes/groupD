#include "cmp_physics.h"
#include "system_physics.h"

using namespace std;
using namespace sf;

using namespace Physics;

void PhysicsComponent::update(double dt) {
  _parent->setPosition(bv2_to_sv2(_body->GetPosition()));
  _parent->setRotation((180 / b2_pi) * _body->GetAngle());
}

PhysicsComponent::PhysicsComponent(Entity* p, bool dyn,
                                   const Vector2f& size)
    : Component(p), _dynamic(dyn) {

  b2BodyDef BodyDef;
  // Is Dynamic(moving), or static(Stationary)
  BodyDef.type = _dynamic ? b2_dynamicBody : b2_staticBody;
  BodyDef.position = sv2_to_bv2(/*invert_height*/(p->getPosition() + (0.5f * size)));
  _data = new bodyUserData();
  _data->_parent = p;
  _data->_tag = "Collidor";
  BodyDef.userData = _data;
  // Create the body
  _body = Physics::GetWorld()->CreateBody(&BodyDef);
  _body->SetActive(true);
  {
    // Create the fixture shape
    b2PolygonShape Shape;
    // SetAsBox box takes HALF-Widths!
    Shape.SetAsBox(sv2_to_bv2(size).x * 0.5f, sv2_to_bv2(size).y * 0.5f);
    b2FixtureDef FixtureDef;
    // Fixture properties
    // FixtureDef.density = _dynamic ? 10.f : 0.f;
    FixtureDef.friction = _dynamic ? 0.1f : 0.8f;
    FixtureDef.restitution = .2;
    FixtureDef.shape = &Shape;
    // Add to body
    _fixture = _body->CreateFixture(&FixtureDef);
    //_fixture->SetRestitution(.9)
    FixtureDef.restitution = .2;
  }

  // An ideal Pod/capusle shape should be used for hte player,
  // this isn't built into B2d, but we can combine two shapes to do so.
  // This would allwo the player to go up steps
  /*
    BodyDef.bullet = true;
    b2PolygonShape shape1;
    shape1.SetAsBox(sv2_to_bv2(size).x * 0.5f, sv2_to_bv2(size).y * 0.5f);
    {
      b2PolygonShape poly ;
      poly.SetAsBox(0.45f, 1.4f);
      b2FixtureDef FixtureDefPoly;

      FixtureDefPoly.shape = &poly;
      _body->CreateFixture(&FixtureDefPoly);

    }
    {
      b2CircleShape circle;
      circle.m_radius = 0.45f;
      circle.m_p.Set(0, -1.4f);
      b2FixtureDef FixtureDefCircle;
      FixtureDefCircle.shape = &circle;
      _body->CreateFixture(&FixtureDefCircle);
    }
  */
}

void PhysicsComponent::setFriction(float r) { _fixture->SetFriction(r); }

void PhysicsComponent::setMass(float m) { _fixture->SetDensity(m); }

void PhysicsComponent::teleport(const sf::Vector2f& v) {
  _body->SetTransform(sv2_to_bv2(invert_height(v)), 0.0f);
}

const sf::Vector2f PhysicsComponent::getVelocity() const {
  return bv2_to_sv2(_body->GetLinearVelocity(), true);
}
void PhysicsComponent::setVelocity(const sf::Vector2f& v) {
  _body->SetLinearVelocity(sv2_to_bv2(v, true));
}

b2Fixture* const PhysicsComponent::getFixture() const { return _fixture; }

PhysicsComponent::~PhysicsComponent() {
  auto a = Physics::GetWorld();
  _body->SetActive(false);
  _data = nullptr;
  Physics::GetWorld()->DestroyBody(_body);
  // delete _body;
  _body = nullptr;
  _fixture = nullptr;
}

void PhysicsComponent::render() {}

void PhysicsComponent::impulse(const sf::Vector2f& i) {
  auto a = b2Vec2(i.x, i.y * -1.0f);
  _body->ApplyLinearImpulseToCenter(a, true);
}

void PhysicsComponent::dampen(const sf::Vector2f& i) {
  auto vel = _body->GetLinearVelocity();
  vel.x *= i.x;
  vel.y *= i.y;
  _body->SetLinearVelocity(vel);
}

bool PhysicsComponent::isTouching(const PhysicsComponent& pc) const {
  b2Contact* bc;
  return isTouching(pc, bc);
}

bool PhysicsComponent::isTouching(const PhysicsComponent& pc,
                                  b2Contact const* bc) const {
  const auto _otherFixture = pc.getFixture();
  const auto& w = *Physics::GetWorld();
  const auto contactList = w.GetContactList();
  const auto clc = w.GetContactCount();
  for (int32 i = 0; i < clc; i++) {
    const auto& contact = (contactList[i]);
    if (contact.IsTouching() && ((contact.GetFixtureA() == _fixture &&
                                  contact.GetFixtureA() == _otherFixture) ||
                                 (contact.GetFixtureA() == _otherFixture &&
                                  contact.GetFixtureA() == _fixture))) {
      bc = &contact;
      return true;
    }
  }
  return false;
}

std::vector<const b2Contact const*> PhysicsComponent::getTouching() const {
  std::vector<const b2Contact const*> ret;

  b2ContactEdge* edge = _body->GetContactList();
  while (edge != NULL) {
    const b2Contact* contact = edge->contact;
    if (contact->IsTouching()) {
      ret.push_back(contact);
    }
    edge = edge->next;
  }

  return ret;
}

void PhysicsComponent::setRestitution(float r) {
  _fixture->SetRestitution(r);
}

PhysicsTriggerComponent::PhysicsTriggerComponent(Entity* p, const Vector2f& size, bool isGoal, bool isActive) 
    : Component(p), _dynamic(false), _isGoal(isGoal), _isActive(isActive), goalReached(false), _playerOverlap(false) {
    b2BodyDef BodyDef;
    BodyDef.type = b2_staticBody;
    BodyDef.position = sv2_to_bv2((p->getPosition() + (0.5f * size)));
    _data = new bodyUserData();
    _data->_parent = p;
    _data->_tag = "Sensor";
    BodyDef.userData = _data;
    // Create the body
    _body = Physics::GetWorld()->CreateBody(&BodyDef);
    _body->SetActive(true);
    // Create the fixture shape
    b2PolygonShape Shape;
    // SetAsBox box takes HALF-Widths!
    Shape.SetAsBox(sv2_to_bv2(size).x * 0.5f, sv2_to_bv2(size).y * 0.5f);
    b2FixtureDef FixtureDef;
    FixtureDef.shape = &Shape;
    FixtureDef.isSensor = true;
    // Add to body
    _fixture = _body->CreateFixture(&FixtureDef);

    std::vector<const b2Contact const*> ret;
    b2ContactEdge* edge = _body->GetContactList();
    while (edge != NULL) {
        const b2Contact* contact = edge->contact;
        if (contact->IsTouching()) {
            ret.push_back(contact);
        }
        edge = edge->next;
    }
    _dirtyCheck = ret;

    //Checkpoint Sound
    checkpointSoundBuffer.loadFromFile("res/music/Checkpoint.mp3");
    checkpointSound.setBuffer(checkpointSoundBuffer);
    checkpointSound.setVolume(70);
}

bool PhysicsTriggerComponent::HasGoalBeenReached() {
    return goalReached;
}

bool PhysicsTriggerComponent::IsActive() {
    return _isActive;
}

void PhysicsTriggerComponent::SetActive(bool active) {
    _isActive = active;
}

void PhysicsTriggerComponent::IsPlayerOverlapping() {
    std::vector<const b2Contact const*> ret;
    b2ContactEdge* edge = _body->GetContactList();
    while (edge != NULL) {
        const b2Contact* contact = edge->contact;
        if (contact->IsTouching() && contact->GetFixtureA()->GetUserData() != "AI" && contact->GetFixtureB()->GetUserData() != "AI") {
            ret.push_back(contact);
        }
        edge = edge->next;
    }
    if (_dirtyCheck != ret && ret.size() > _dirtyCheck.size()) {
        for (auto ent : ret) {
            auto bodyA = (bodyUserData*)ent->GetFixtureA()->GetBody()->GetUserData();
            auto bodyB = (bodyUserData*)ent->GetFixtureB()->GetBody()->GetUserData();
            if (bodyA->_tag == "Player" || bodyB->_tag == "Player") {
                printf("Successfully detected Player\n");
                _dirtyCheck = ret;
                _playerOverlap = true;
                if (_isGoal) {
                    goalReached = true;
                    //Checkpoint Sound
                    checkpointSound.play();
                }
            }
        }
    }
    else if (_dirtyCheck.size() > ret.size()) {
        printf("Player has left detection area\n");
        _playerOverlap = false;
        _dirtyCheck = ret;
    }
}

void PhysicsTriggerComponent::render() {}

void PhysicsTriggerComponent::update(double dt) {
    if (_isActive) {
        IsPlayerOverlapping();
    }
}

PhysicsTriggerComponent::~PhysicsTriggerComponent() {
    auto a = Physics::GetWorld();
    _body->SetActive(false);
    _data = nullptr;
    Physics::GetWorld()->DestroyBody(_body);
    // delete _body;
    _body = nullptr;
    _fixture = nullptr;
}

void GrateComponent::update(double dt) {
    PhysicsTriggerComponent::update(dt);
    if (_playerOverlap && !_toReset) {
        for (const auto& b : *_birds) {
            auto pos = b->getPosition();
            if (sf::Vector2f(pos - _parent->getPosition()).lengthSq() < pow((ls::getTileSize() * 5), 2)) {
                auto cmp = b->GetCompatibleComponent<AIBirdComponent>();
                if (cmp.size() > 0 && cmp[0] != nullptr) {
                    cmp[0]->SetChasing(true);
                    _toReset = true;
                }
            }
        }
    }
    else if (!_playerOverlap && _toReset) {
        _toReset = false;
    }
}

GrateComponent::~GrateComponent() {
    _birds->clear();
    _birds = nullptr;
}