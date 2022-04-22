#include "scene_Scoreboard.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace sf; 

void Scoreboard::Load() {
	tag = -5; 

	int counter = 0; 
	vector<string> lines; 
	vector<shared_ptr<Entity>> scoreboardText; 
	std::string line; 
	ifstream timeFile; 

	timeFile.open("times.txt", std::ios_base::in);
	if (timeFile.is_open()) {
		while (!timeFile.eof()) {
			line.resize(timeFile.tellg()); 
			timeFile >> line; 
		}
	}

	//Split lines at blank spaces. https://www.delftstack.com/howto/cpp/cpp-split-string-by-space/
	//This should allow the output to be a list. 
	string spaceDelimiter = " "; 
	int stingPosition = 0; 

	while ((stingPosition = line.find(spaceDelimiter)) != string::npos) {
		lines.push_back(line.substr(0, stingPosition));
		line.erase(0, stingPosition + spaceDelimiter.length());
		counter++;
	}

	//Removing underscores for readability
	for (int i = 0; i < lines.size(); i++) {
		for (int j = 0; j < lines[i].length(); j++) {
			if (lines[i][j] == '_') {
				lines[i][j] = ' '; 
			}
		}
	}

	auto esc = makeEntity();
	esc->setPosition(Vector2f(5, 5));
	auto t = esc->addComponent<ESCTextComponent>("Press ESC to return to menu");

	for (int i = 0; i < counter; i++) {
		auto txt = makeEntity();
		scoreboardText.push_back(txt);
	}

	for (int i = 0; i < counter; i++) {
		scoreboardText[i]->setPosition(Vector2f(Engine::getWindowSize().x * 0.3, Engine::getWindowSize().y * (0.2 + (i * 30))));
		auto s = scoreboardText[i]->addComponent<TextComponent>(std::to_string(i+1) + " " + lines[i] + "\n ");
	}
	timeFile.close(); 
	setLoaded(true);
}

void Scoreboard::UnLoad() {
	Scene::UnLoad();
}

void Scoreboard::Update(const double& dt) {
	Scene::Update(dt);
}

void Scoreboard::Render() {
	Scene::Render();
}