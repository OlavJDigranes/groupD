#pragma once
#include <algorithm>
#include <memory>
#include <typeindex>
#include <vector>
#include "maths.h" //NOTE: brings in use of SFML sf namespace

class Component; //forward declare

//	Entity Base Class
class Entity {

protected:
	std::vector<std::shared_ptr<Component>> _components;	// Components attached to entity
	sf::Vector2f _position;	//	Current position
	float _rotation;	//	Current Rotation
	bool _alive;	//	should be updated
	bool _visible;	//	should be rendered
	bool _fordeletion;	//	should be deleted
public:
	Entity();
	virtual ~Entity();
	virtual void update(double dt);
	virtual void render();

	const sf::Vector2f& getPosition() const;
	void setPosition(const sf::Vector2f& Position);
	bool is_fordeletion() const;
	float getRotation() const;
	void setRotation(float _rotation);
	bool isAlive() const;
	void setAlive(bool _alive);
	void setForDelete();
	bool isVisible() const;
	void setVisible(bool _visible);

	//	Template for adding component of type
	template <typename T, typename... Targs>
	std::shared_ptr<T> addComponent(Targs... params) {
		static_assert(std::is_base_of<Component, T>::value, "T != component");
		std::shared_ptr<T> sp(std::make_shared<T>(this, params...));
		_components.push_back(sp);
		return sp;
	}

	//	Template for getting all components attached to entity
	template <typename T>
	const std::vector<std::shared_ptr<T>> get_components() const {
		static_assert(std::is_base_of<Component, T>::value, "T != component");
		std::vector<std::shared_ptr<T>> ret;
		for (const auto c : _components) {
			if (typeid(*c) == typeid(T)) {
				ret.push_back(std::dynamic_pointer_cast<T>(c));
			}
		}
		return std::move(ret);
	}

	//	Template for getting all components deriving from T class that are attached to entity
	template <typename T>
	const std::vector<std::shared_ptr<T>> getCompatibleComponent() {
		static_assert(std::is_base_of<Component, T>::value, "T != component");
		std::vector<std::shared_ptr<T>> ret;
		for (auto c : _components) {
			auto dd = dynamic_cast<T*>(&(*c));
			if (dd) {
				ret.push_back(std::dynamic_pointer_cast<T>(c));
			}
		}
		return ret;
	}
};

//	Entity Manager 
struct EntityManager {
	std::vector<std::shared_ptr<Entity>> list; //	List of all managed entities
	void update(double dt);
	void render();
};

//	Component
class Component {
protected:
	Entity* const _parent;	//	Parent entity
	bool _fordeletion;	//	should remove entity
	explicit Component(Entity* const p);	//	explicit constructor for parent ownership

public:
	Component() = delete;
	bool is_fordeletion() const;
	virtual void update(double dt) = 0;
	virtual void render() = 0;
	virtual ~Component();
};