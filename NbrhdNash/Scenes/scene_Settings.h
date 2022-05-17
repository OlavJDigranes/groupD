#pragma once

#include "LevelSystem.h"
#include "engine.h"
#include "components/cmp_sprite.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include "components/components.h"

using namespace std;
using namespace sf;

//Settings scene class
class Settings : public Scene {
protected:
	ofstream settingsFile;
	vector<string> lines;
	int counter = 0;
	int selectedOption;
	std::vector<std::shared_ptr<Entity>> menuOptions;
	std::vector<std::shared_ptr<TextComponent>> menuTexts;
	float btnTimer3 = 1.0f;
public:
	string vsyncSetting;
	string imageSetting;

	Settings() = default; 
	~Settings() = default; 

	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;

	void ingestFile();
	void saveSettings();
};