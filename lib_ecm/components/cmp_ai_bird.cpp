#include "cmp_ai_bird.h"

AIBirdComponent::AIBirdComponent(Entity* parent, std::shared_ptr<Entity> player, sf::Vector2i levelBounds, sf::Vector2f size) : Component(parent), _player(player) {
	_str = std::make_shared<BirdSteering>(parent, player.get(), false, levelBounds);
    _sm = std::make_unique<StateMachineComponent>(parent);
    _sm->addState("Waiting", std::make_shared<WaitingState>());
    _sm->addState("Chasing", std::make_shared<ChasingState>());
    _sm->addState("ReturnHome", std::make_shared<ReturningHomeState>());
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
    _sm->changeState("Waiting");
    homeLoc = _parent->getPosition();

    //Sounds
    splatBuffer.loadFromFile("res/music/BirdSplat.mp3");
    flyingBuffer.loadFromFile("res/music/PigeonFlight.mp3");
    birdQueBuffer.loadFromFile("res/music/BirdQue.mp3"); 

    splat.setBuffer(splatBuffer);
    flying.setBuffer(flyingBuffer); 
    birdQue.setBuffer(birdQueBuffer); 

    splat.setVolume(70);
    flying.setVolume(65); 
    birdQue.setVolume(65); 
}

void AIBirdComponent::CheckForPlayer(double dt) {
    std::vector<const b2Contact const*> ret;
    b2ContactEdge* edge = _body->GetContactList();
    while (edge != NULL) {
        const b2Contact* contact = edge->contact;
        if (contact->IsTouching()) {
            ret.push_back(contact);
        }
        edge = edge->next;
    }
    bool test = _dirtyCheck != ret && ret.size() > _dirtyCheck.size();
    if (_dirtyCheck != ret && ret.size() > _dirtyCheck.size()) {
        auto bodyA = (bodyUserData*)ret.back()->GetFixtureA()->GetBody()->GetUserData();
        auto bodyB = (bodyUserData*)ret.back()->GetFixtureB()->GetBody()->GetUserData();
        if (bodyA->_tag == "Player" || bodyB->_tag == "Player") {
            //printf("Successfully detected Player\n");
            _dirtyCheck = ret;
            _overPlayer = true;
        }
    }
    else if (_dirtyCheck.size() > ret.size()) {
        //printf("Player has left detection area\n");
        _dirtyCheck = ret;
        _overPlayer = false;
    }
}

void AIBirdComponent::update(double dt) {
    if (_isChasing) {
        if (_sm->currentState() != "Chasing") {
            _sm->changeState("Chasing");
            birdQue.play(); 
            flying.play(); 
            flying.setLoop(true); 
        }
        CheckForPlayer(dt);
        if (_isChasing && sf::Vector2f(_parent->getPosition() - _player->getPosition()).lengthSq() > pow(ls::getTileSize() * 10, 2)) {
            _isChasing = false;
            _sm->changeState("ReturnHome");
        }
    }
    if (_overPlayer && _isChasing) {
        _timeToPoop += dt;
        //printf("poop time = %f\n", _timeToPoop);
    }
    if (_isChasing && _timeToPoop > 1) {
        auto p = _player->get_components<PlayerDataComponent>();
        if (p[0] != nullptr) {
            p[0]->TakeDamage(10);
            //printf("Health: %i\n", p[0]->GetHealth());
        }
        splat.play(); 
        _isChasing = false;
        _timeToPoop = 0;
        _sm->changeState("ReturnHome");
    }
    if (sf::Vector2f(_parent->getPosition() - GetHomeLocation()).lengthSq() < pow(5, 2) && _sm->currentState() == "ReturnHome") {
        flying.stop(); 
        _sm->changeState("Waiting");
    }
    _body->SetTransform(Physics::sv2_to_bv2(_parent->getPosition()), 0);
    _str->update(dt);
    _sm->update(dt);
}

AIBirdComponent::~AIBirdComponent() {
	_str.reset();
    _sm.reset();
	_body = nullptr;
	Component::~Component();
}