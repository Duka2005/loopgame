#include <vector>
#include <random>
#include "../Headers/GenLevel.hpp"
#include "../Headers/Level.hpp"
#include "../Headers/Tileset.hpp"
#include "../Headers/Window.hpp"
#include "../Headers/Mario.hpp"
#include "../Headers/GameClass.hpp"

std::random_device rd;
std::vector<Level> lvldata;
std::uniform_int_distribution<int> dist(1, 11);
int global_pos = 2;
int global_prev = 0;

//make a random number
int RandomUntilUnique() {
	int ran = dist(rd);
	while (global_prev == ran) {
		ran = dist(rd);
	}
	global_prev = ran;
	return ran;
}

std::string getRandomLevel() {
	std::string out = "Levels/level_"+std::to_string(RandomUntilUnique())+".txt";
	return out;
}

//level map starter when game is start
void LevelInit() {
	lvldata.push_back(Level());
	GenLevel(lvldata.back(), "Levels/level_0.txt", 0);
	lvldata.push_back(Level());
	GenLevel(lvldata.back(), getRandomLevel(), 1);
	lvldata.push_back(Level());
	GenLevel(lvldata.back(), getRandomLevel(), 2);
}

//generate new level map in bottom
void CheckLevelAvaliable() {
	if (initx > (lvldata[0].pos + 2) * 1280) {
		lvldata.erase(lvldata.begin(), lvldata.begin()+1);
		for (int i = 0; i < lvldata.size(); ++i)
			lvldata[i].pos = i;
		lvldata.push_back(Level());
		GenLevel(lvldata.back(), getRandomLevel(), 2);
		initx -= 1280.0f;
		mario.setPosition({mario.getPosition().x - 1280.0f, mario.getPosition().y});
	}
}
void LevelUpdatePos() {
	for (int i = 0; i < lvldata.size(); ++i) {
		lvldata[i].UpdateTilePosition();
		lvldata[i].UpdateEnemyPosition();
	}
}

//draw level map in screen
void LevelDraw() {
	for (const auto& i : lvldata) {
		for (const auto& j : i.data) {
			rTexture.draw(j);
		}
	}
}