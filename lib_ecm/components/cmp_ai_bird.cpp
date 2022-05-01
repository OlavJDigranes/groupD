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
    flyingBuffer1.loadFromFile("res/music/PigeonFlight1.mp3");
    flyingBuffer2.loadFromFile("res/music/PigeonFlight2.mp3");
    flyingBuffer3.loadFromFile("res/music/PigeonFlight3.mp3");
    birdQueBuffer.loadFromFile("res/music/BirdQue.mp3"); 

    splat.setBuffer(splatBuffer);
    flying1.setBuffer(flyingBuffer1); 
    flying2.setBuffer(flyingBuffer2); 
    flying3.setBuffer(flyingBuffer3); 
    birdQue.setBuffer(birdQueBuffer); 

    splat.setVolume(70);
    flying1.setVolume(65); 
    flying2.setVolume(65); 
    flying3.setVolume(65); 
    birdQue.setVolume(55); 
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
            randNum = rand() % 3; 
            if (randNum == 0) {
                flying1.play();
                flying1.setLoop(true);
            }
            if (randNum == 1) {
                flying2.play();
                flying2.setLoop(true);
            }
            if (randNum == 2) {
                flying3.play();
                flying3.setLoop(true);
            }
            
        }
        CheckForPlayer(dt);
        if (_isChasing && sf::Vector2f(_parent->getPosition() - _player->getPosition()).lengthSq() > pow(ls::getTileSize() * 10, 2)) {
            _isChasing = false;
            _sm->changeState("ReturnHome");
        }
    }
    if (_overPlayer && _isChasing) {
        _timeToPoop += dt;
    }
    if (_isChasing && _timeToPoop > 1) {
        auto p = _player->get_components<PlayerDataComponent>();
        if (p[0] != nullptr) {
            p[0]->TakeDamage(10);
        }
        splat.play(); 
        _isChasing = false;
        _timeToPoop = 0;
        _sm->changeState("ReturnHome");
    }
    if (sf::Vector2f(_parent->getPosition() - GetHomeLocation()).lengthSq() < pow(5, 2) && _sm->currentState() == "ReturnHome") {
        flying1.stop(); 
        flying2.stop(); 
        flying3.stop(); 
        _sm->changeState("Waiting");
    }
    
    _body->SetTransform(Physics::sv2_to_bv2(_parent->getPosition()), _body->GetAngle());
    _str->update(dt);
    _sm->update(dt);
}

AIBirdComponent::~AIBirdComponent() {
	_str.reset();
    _sm.reset();
	_body = nullptr;
	Component::~Component();
}