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
			lines.push_back(line);
			counter++;

			//Make a vector of 5 text elements.
				//Put them off screen?
			if (counter == 1) {
				auto txt1 = makeEntity();
				scoreboardText.push_back(txt1);
			}
			if (counter == 2) {
				auto txt2 = makeEntity();
				scoreboardText.push_back(txt2);
			}
			if (counter == 3) {
				auto txt3 = makeEntity();
				scoreboardText.push_back(txt3);
			}
			if (counter == 4) {
				auto txt4 = makeEntity();
				scoreboardText.push_back(txt4);
			}
			if (counter == 5) {
				auto txt5 = makeEntity();
				scoreboardText.push_back(txt5);
			}
		}
	}

	//Split lines at blank spaces. https://www.delftstack.com/howto/cpp/cpp-split-string-by-space/
	//This should allow the output to be a list. 
	/*
	string spaceDelimiter = " "; 
	int stingPosition = 0; 

	while ((stingPosition = line.find(spaceDelimiter)) != string::npos) {
		lines.push_back(line.substr(0, stingPosition));
		line.erase(0, stingPosition + spaceDelimiter.length());
		counter++;
	}
	*/

	//Removing underscores for readability
	for (int i = 0; i < lines.size(); i++) {
		std::cout << "$$$" + lines[i] << endl; 
		for (int j = 0; j < lines[i].length(); j++) {
			if (lines[i][j] == '_') {
				lines[i][j] = ' '; 
			}
		}
	}

	//Escape text
	auto esc = makeEntity();
	esc->setPosition(Vector2f(5, 5));
	auto t = esc->addComponent<ESCTextComponent>("Press ESC to return to menu");

	
	
	std::cout << "TBTBT1 " + std::to_string(counter) << endl;

	//Populate the elements if needed, and place on screen. 
	for (int i = 0; i < counter; i++) {
		std::cout << std::to_string(i) << endl; 
		//auto txt = makeEntity();
		//scoreboardText.push_back(txt);
		scoreboardText[i]->setPosition(Vector2f(Engine::getWindowSize().x * 0.3, Engine::getWindowSize().y * (0.2 + ((size_t)i * 30))));
		auto s = scoreboardText[i]->addComponent<TextComponent>(std::to_string(i + 1) + " " + lines[i]);
	}

	/*
	if (counter == 1) {
		auto txt1 = makeEntity();
		scoreboardText.push_back(txt1);
		scoreboardText[0]->setPosition(Vector2f(Engine::getWindowSize().x * 0.3, Engine::getWindowSize().y * (0.2)));
		auto s = scoreboardText[0]->addComponent<TextComponent>("1: " + lines[0]);
	}
	if (counter == 2) {
		auto txt2 = makeEntity();
		scoreboardText.push_back(txt2);
		scoreboardText[1]->setPosition(Vector2f(Engine::getWindowSize().x * 0.3, Engine::getWindowSize().y * (0.2 + 30)));
		auto s = scoreboardText[1]->addComponent<TextComponent>("2: " + lines[1]);
	}
	if (counter == 3) {
		auto txt3 = makeEntity();
		scoreboardText.push_back(txt3);
		scoreboardText[2]->setPosition(Vector2f(Engine::getWindowSize().x * 0.3, Engine::getWindowSize().y * (0.2 + 60)));
		auto s = scoreboardText[2]->addComponent<TextComponent>("3: " + lines[2]);
	}
	if (counter == 4) {
		auto txt4 = makeEntity();
		scoreboardText.push_back(txt4);
		scoreboardText[3]->setPosition(Vector2f(Engine::getWindowSize().x * 0.3, Engine::getWindowSize().y * (0.2 + 90)));
		auto s = scoreboardText[3]->addComponent<TextComponent>("4: " + lines[3]);
	}
	if (counter == 5) {
		auto txt5 = makeEntity();
		scoreboardText.push_back(txt5);
		scoreboardText[4]->setPosition(Vector2f(Engine::getWindowSize().x * 0.3, Engine::getWindowSize().y * (0.2 + 120)));
		auto s = scoreboardText[4]->addComponent<TextComponent>("5: " + lines[4]);
	}
	*/

	for (int i = 0; i < counter; i++) {
		
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