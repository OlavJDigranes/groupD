#include "ecm.h"

// --- Entity class declarations ---

Entity::Entity() : _components(std::vector<std::shared_ptr<Component>>()), _position(sf::Vector2f(0, 0)),
_rotation(0), _alive(false), _visible(false), _fordeletion(false)
{};

Entity::~Entity() {
	if (_fordeletion) {
		for (auto item : _components) {
			item = nullptr;
		}
	}
	else {
		throw "Attempting to delete item that is not marked for deletion!";
	}
}

//	Render method - Called by entity manager
void Entity::render() {
	if (_visible)
	{
		for (auto item : _components) {
			item->render();
		}
	}
};

//	Update method - Called by entity manager
void Entity::update(double dt) {
	if (_alive)
	{
		for (auto item : _components) {
			item->update(dt);
		}
	}
};

//	Get position of entity
const sf::Vector2f& Entity::getPosition() const {
	return _position;
};

//	Set entity position
void Entity::setPosition(const sf::Vector2f& Position) {
	_position = Position;
};

//	Get if entity has been marked for deletion
bool Entity::is_fordeletion() const {
	return _fordeletion;
};

//	Set entity for deletion
void Entity::setForDelete() {
	_fordeletion = true;
};

//	Get rotation of entity
float Entity::getRotation() const {
	return _rotation;
};

//	Set entity rotation
void Entity::setRotation(float Rotation) {
	_rotation = Rotation;
};

//	Get if entity is alive
bool Entity::isAlive() const {
	return _alive;
};

// Set if entity should be alive
void Entity::setAlive(bool Alive) {
	_alive = Alive;
};

//	Get if entity is currently visible
bool Entity::isVisible() const {
	return _visible;
};

//	Set if entity should be visible
void Entity::setVisible(bool IsVisible) {
	_visible = IsVisible;
};

// --- Entity Manager declarations ---
// 
//	Update method - Updates all held entities
void EntityManager::update(double dt) {
	for (auto item : list) {
		item->update(dt);
	}
}

//	Render method - Render all held entities
void EntityManager::render() {
	for (auto item : list) {
		item->render();
	}
}

// Component class declarations
Component::Component(Entity* const Parent) : _parent(Parent), _fordeletion(false) {};

//	Get if component is set for deletion
bool Component::is_fordeletion() const {
	return _fordeletion;
};

//	Update method (abstract)
void Component::update(double dt) {};

//	Render method (abstract)
void Component::render() {};

Component::~Component() {};