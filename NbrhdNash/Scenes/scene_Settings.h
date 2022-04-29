#pragma once

#include "LevelSystem.h"
#include "engine.h"
#include "components/cmp_sprite.h"
#include <fstream>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace sf;

//Settings scene class
class Settings : public Scene {
protected:
	ofstream settingsFile;
	vector<string> lines;
	int counter = 0;
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