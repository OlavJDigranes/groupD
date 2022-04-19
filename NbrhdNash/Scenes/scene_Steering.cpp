#include "scene_steering.h"
#include "components/cmp_sprite.h"
#include "components/cmp_actor_movement.h"
#include "components/cmp_movement.h"
#include "components/cmp_ai_steering.h"
#include <LevelSystem.h>
#include <random>
#include <chrono>


using namespace std;
using namespace std::chrono;
using namespace sf;

void SteeringScene::Load() {
    auto player = makeEntity();
    player->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2,
        Engine::GetWindow().getSize().y / 2));
    auto s = player->addComponent<ShapeComponent>();
    s->setShape<CircleShape>(10.0f);
    s->getShape().setFillColor(Color::Red);
    player->addComponent<BasicMovementComponent>();

    // Setup C++ random number generation
    random_device dev;
    default_random_engine engine(dev());
    uniform_real_distribution<float> x_dist(0.0f,
        Engine::GetWindow().getSize().x);
    uniform_real_distribution<float> y_dist(0.0f,
        Engine::GetWindow().getSize().y);
    for (size_t n = 0; n < 100; ++n) {
        auto enemy = makeEntity();
        enemy->setPosition(Vector2f(x_dist(engine), y_dist(engine)));
        auto s = enemy->addComponent<ShapeComponent>();
        s->setShape<CircleShape>(10.0f, 3.0f);
        s->getShape().setFillColor(Color::Blue);
        enemy->addComponent<SteeringComponent>(player.get(), true, sf::Vector2i(ls::getWidth(), ls::getHeight()));
    }

    std::cout << " Scene 1 Load Done" << std::endl;

    setLoaded(true);
}

void SteeringScene::UnLoad() { Scene::UnLoad(); }

void SteeringScene::Update(const double& dt) {
    Scene::Update(dt); 
}

void SteeringScene::Render() { 
    ls::render(Engine::GetWindow());
    Scene::Render();
}