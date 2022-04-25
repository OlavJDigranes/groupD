#pragma once
#include <../lib_ecm/ecm.h>

class PathfindingComponent : public Component {
protected:
	std::shared_ptr<std::vector<sf::Vector2i>> _path;
	std::shared_ptr<size_t> _index;
	double _elapsed = 0.0;

public:
	void update(double) override;
	void render() override {}
	void setPath(std::vector<sf::Vector2i>& path);
	std::shared_ptr<std::vector<sf::Vector2i>> getPath() { return _path; };
	std::shared_ptr<size_t> getIndex() { return _index; };
	void FindNewCheckpoint();
	explicit PathfindingComponent(Entity* p);
	PathfindingComponent() = delete;
	~PathfindingComponent();
};