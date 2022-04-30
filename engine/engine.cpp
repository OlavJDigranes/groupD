#include "engine.h"
#include "maths.h"
#include "system_physics.h"
#include "system_renderer.h"
#include "system_resources.h"
#include <SFML/Graphics.hpp>
#include <future>
#include <iostream>
#include <stdexcept>
#include "../NbrhdNash/game.h"
#include "SFML/Window.hpp"
#include "SFML/Window/Joystick.hpp"

using namespace sf;
using namespace std;
Scene* Engine::_activeScene = nullptr;
std::string Engine::_gameName;
float Engine::btnTimer; //Rest timer so holding the button won't be read. 

static bool loading = false;
static float loadingspinner = 0.f;
static float loadingTime;
static RenderWindow* _window;

void Loading_update(float dt, const Scene* const scn) {
  //  cout << "Eng: Loading Screen\n";
  if (scn->isLoaded()) {
    //cout << "Eng: Exiting Loading Screen\n";
    loading = false;
  } else {
    loadingspinner += 220.0f * dt;
    loadingTime += dt;
  }
}
void Loading_render() {
  // cout << "Eng: Loading Screen Render\n";
  static CircleShape octagon(80, 8);
  octagon.setOrigin(Vector2f(80, 80));
  octagon.setRotation(sf::degrees(loadingspinner));
  octagon.setPosition(Vcast<float>(Engine::getWindowSize()) * .5f);
  octagon.setFillColor(Color(255,255,255,min(255.f,40.f*loadingTime)));
  static Text t("Loading", *Resources::get<sf::Font>("arial.ttf"));
  t.setFillColor(Color(255,255,255,min(255.f,40.f*loadingTime)));
  t.setPosition(Vcast<float>(Engine::getWindowSize()) * Vector2f(0.4f,0.3f));
  Renderer::queue(&t);
  Renderer::queue(&octagon);
}

float frametimes[256] = {};
uint8_t ftc = 0;

void Engine::Update() {
  static sf::Clock clock;
  float dt = clock.restart().asSeconds();
  {
    frametimes[++ftc] = dt;
    static string avg = _gameName + " FPS:";
    if (ftc % 60 == 0) {
      double davg = 0;
      for (const auto t : frametimes) {
        davg += t;
      }
      davg = 1.0 / (davg / 255.0);
      _window->setTitle(avg + toStrDecPt(2, davg));
    }
  }

  if (btnTimer > 0) {
      btnTimer -= dt; 
  }

  if (loading) {
    Loading_update(dt, _activeScene);
  } else if (_activeScene != nullptr) {
    Physics::update(dt);
    _activeScene->Update(dt);
  }
}

void Engine::Render(RenderWindow& window) {
  if (loading) {
    Loading_render();
  } else if (_activeScene != nullptr) {
    _activeScene->Render();
  }

  Renderer::render();
}

void Engine::Start(unsigned int width, unsigned int height,
                   const std::string& gameName, Scene* scn) {
    btnTimer = 0; 
  //RenderWindow window(VideoMode(width, height), gameName, sf::Style::Fullscreen);
  RenderWindow window(VideoMode(width, height), gameName, sf::Style::Close);
  _gameName = gameName;
  _window = &window;
  Renderer::initialise(window);
  Physics::initialise();
  ChangeScene(scn);
  while (window.isOpen()) {
    Event event;
    while (window.pollEvent(event)) {
      if (event.type == Event::Closed) {
        window.close();
      }
      //Window resizing
      //https://www.sfml-dev.org/tutorials/2.2/graphics-view.php#showing-more-when-the-window-is-resized
      if (event.type == sf::Event::Resized) {
          sf::FloatRect screenSize(Vector2f(0, 0), Vector2f(event.size.width, event.size.height));
          window.setView(sf::View(screenSize)); 
      }
    }

    //Window resizing actions
    if (_activeScene->resTag == 1) {
        int w = 1280; 
        int h = 720;
        sf::FloatRect screenSize1(Vector2f(0, 0), Vector2f(w, h));
        window.setView(sf::View(screenSize1));
        //sf::VideoMode(w, h);
        window.setSize(Vector2u(w, h));
    }
    if (_activeScene->resTag == 2) {
        int w = 1920;
        int h = 1080;
        sf::FloatRect screenSize2(Vector2f(0, 0), Vector2f(w, h));
        window.setView(sf::View(screenSize2));
        //sf::VideoMode(1920, 1080);
        window.setSize(Vector2u(w, h));
    }
    if (_activeScene->resTag == 3) {
        int w = 2560;
        int h = 1440;
        sf::FloatRect screenSize3(Vector2f(0, 0), Vector2f(w, h));
        window.setView(sf::View(screenSize3));
        //sf::VideoMode(2560, 1440);
        window.setSize(Vector2u(w, h));
    }

    //Escape key handling. It is only meant to exit the game if pressed in the main menu. Elsewise it should return to main menu. The scenes are identified by the tag 
    if (Keyboard::isKeyPressed(Keyboard::Escape) && btnTimer <= 0.0f) {
        if (_activeScene->tag == 0) {
            window.close();
        }
        if (_activeScene->tag == 1 || _activeScene->tag == -1 || _activeScene->tag == -2 || _activeScene->tag == -3 || _activeScene->tag == -4 || _activeScene->tag == -5) {
            ChangeScene(&menu);
        }
        
        btnTimer = 1.3f; 
        
    }

    //Joystick handling for ESC
    sf::Joystick::Identification joystickID = sf::Joystick::getIdentification(0);
    if (Joystick::isConnected(0)) {
        if (Joystick::isButtonPressed(0, 7) && btnTimer <= 0.0f) {
            if (_activeScene->tag == 0) {
                window.close();
            }
            if (_activeScene->tag == 1 || _activeScene->tag == -1 || _activeScene->tag == -2 || _activeScene->tag == -3 || _activeScene->tag == -4 || _activeScene->tag == -5) {
                ChangeScene(&menu);
            }

            btnTimer = 1.3f;
        }

    }
    if (_activeScene == &L1) {
        if (L1.IsCompleted()) {
            Engine::ChangeScene(&celebration);
        }
        else if (L1.HasFailedLevel()) {
            Engine::ChangeScene(&gameover);
        }
    }

    window.clear();
    Update();
    Render(window);
    window.display();
  }
  if (_activeScene != nullptr) {
    _activeScene->UnLoad();
    _activeScene = nullptr;
  }
  window.close();
  Physics::shutdown();
  // Render::shutdown();
}

std::shared_ptr<Entity> Scene::makeEntity() {
  auto e = make_shared<Entity>(this);
  ents.list.push_back(e);
  return std::move(e);
}

void Engine::setVsync(bool b) { _window->setVerticalSyncEnabled(b); }

void Engine::ChangeScene(Scene* s) {
  //cout << "Eng: changing scene: " << s << endl;
  auto old = _activeScene;
  _activeScene = s;

  if (old != nullptr) {
    old->UnLoad(); // todo: Unload Async
  }

  if (!s->isLoaded()) {
    //cout << "Eng: Entering Loading Screen\n";
    loadingTime =0;
    _activeScene->LoadAsync();
    //_activeScene->Load();
    loading = true;
  }
}

void Scene::Update(const double& dt) { 
    auto test = Engine::GetWindow().getView().getCenter();
    ents.update(dt, Engine::GetWindow().getView().getCenter(), Engine::getWindowSize());
}

void Scene::Render() { ents.render(Engine::GetWindow().getView().getCenter(), Engine::getWindowSize()); }

bool Scene::isLoaded() const {
  {
    std::lock_guard<std::mutex> lck(_loaded_mtx);
    // Are we already loading asynchronously?
    if (_loaded_future.valid() // yes
        &&                     // Has it finished?
        _loaded_future.wait_for(chrono::seconds(0)) ==
            future_status::ready) {
      // Yes
      _loaded_future.get();
      _loaded = true;
    }
    return _loaded;
  }
}
void Scene::setLoaded(bool b) {
  {
    std::lock_guard<std::mutex> lck(_loaded_mtx);
    _loaded = b;
  }
}

void Scene::UnLoad() {
    for (auto e : ents.list) {
        e->setAlive(false);
        e->setForDelete();
    }
    ents.list.clear();
    setLoaded(false);
}

void Scene::LoadAsync() { _loaded_future = std::async(&Scene::Load, this); }

sf::Vector2u Engine::getWindowSize() { return _window->getSize(); }

sf::RenderWindow& Engine::GetWindow() { return *_window; }

namespace timing {
// Return time since Epoc
long long now() {
  return std::chrono::high_resolution_clock::now()
      .time_since_epoch()
      .count();
}
// Return time since last() was last called.
long long last() {
  auto n = now();
  static auto then = now();
  auto dt = n - then;
  then = n;
  return dt;
}
} // namespace timing

Scene::~Scene() { UnLoad(); }