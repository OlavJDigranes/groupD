#include "cmp_ai_bird.h"

AIBirdComponent::AIBirdComponent(Entity* parent, Entity* player, sf::Vector2i levelBounds, sf::Vector2f size) : Component(parent) {
	_str = std::make_unique<SteeringComponent>(parent, player, false, levelBounds);
    b2BodyDef BodyDef;
    BodyDef.type = b2_staticBody;
    BodyDef.position = Physics::sv2_to_bv2((parent->getPosition() + (0.5f * size)));
    _data = new bodyUserData();
    _data->_parent = parent;
    _data->_tag = "Bird";
    BodyDef.userData = _data;
    // Create the body
    _body = Physics::GetWorld()->CreateBody(&BodyDef);
    _body->SetActive(true);
    // Create the fixture shape
    b2PolygonShape Shape;
    // SetAsBox box takes HALF-Widths!
    Shape.SetAsBox(Physics::sv2_to_bv2(size).x * 0.5f, Physics::sv2_to_bv2(size).y * 0.5f);
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
}

void AIBirdComponent::AwaitDisturbance() {
    std::vector<const b2Contact const*> ret;
    b2ContactEdge* edge = _body->GetContactList();
    while (edge != NULL) {
        const b2Contact* contact = edge->contact;
        if (contact->IsTouching()) {
            ret.push_back(contact);
        }
        edge = edge->next;
    }
    if (_dirtyCheck != ret && ret.size() > _dirtyCheck.size()) {
        auto bodyA = (bodyUserData*)ret.back()->GetFixtureA()->GetBody()->GetUserData();
        auto bodyB = (bodyUserData*)ret.back()->GetFixtureB()->GetBody()->GetUserData();
        if (bodyA->_tag == "Grate" || bodyB->_tag == "Grate") {
            printf("Successfully detected Player\n");
            _dirtyCheck = ret;
            _isChasing = true;
        }
    }
    else if (_dirtyCheck.size() > ret.size()) {
        printf("Player has left detection area\n");
        _dirtyCheck = ret;
    }
}

void AIBirdComponent::update(double dt) {
    AwaitDisturbance();
    if (_isChasing) {
        _str->SetActive(true);   
    }
    if (_str->HasArrived()) {
        _isChasing = false;
    }
}

AIBirdComponent::~AIBirdComponent() {
	_str = nullptr;
	_body = nullptr;
	Component::~Component();
}