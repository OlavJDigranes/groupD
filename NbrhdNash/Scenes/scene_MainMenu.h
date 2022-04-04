#pragma once

#include "engine.h"

class MainMenu : public Scene {
public:
	MainMenu() = default;
	~MainMenu() = default;

	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;
};