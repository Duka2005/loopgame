#include <vector>
#include <random>
#include "../Headers/Level.hpp"
#include "../Headers/Tileset.hpp"
#include "../Headers/GenLevel.hpp"
#include "../Headers/Window.hpp"
#include "../Headers/Mario.hpp"

const std::array<std::string, 12> PathLvl{
	"Levels/level_0.txt",
	"Levels/level_1.txt",
	"Levels/level_2.txt",
	"Levels/level_3.txt",
	"Levels/level_4.txt",
	"Levels/level_5.txt",
	"Levels/level_6.txt",
	"Levels/level_7.txt",
	"Levels/level_8.txt",
	"Levels/level_9.txt",
	"Levels/level_10.txt",
	"Levels/level_11.txt"
};
std::random_device rd;
std::vector<Level> lvldata;
std::uniform_int_distribution<int> dist(1, 11);
int global_pos = 2;
int global_prev = 0;
int RandomUntilUnique() {
	int ran = dist(rd);
	while (global_prev == ran) {
		ran = dist(rd);
	}
	global_prev = ran;
	return ran;
}
void LevelInit() {
	lvldata.push_back(Level());
	GenLevel(lvldata.back(), PathLvl[0], 0);
	lvldata.push_back(Level());
	GenLevel(lvldata.back(), PathLvl[RandomUntilUnique()], 1);
	lvldata.push_back(Level());
	GenLevel(lvldata.back(), PathLvl[RandomUntilUnique()], 2);
}
void CheckLevelAvaliable() {
	if (mario.getPosition().x > (lvldata[0].pos + 2) * 1280) {
		++global_pos;
		lvldata.erase(lvldata.begin(), lvldata.begin()+1);
		lvldata.push_back(Level());
		GenLevel(lvldata.back(), PathLvl[RandomUntilUnique()], global_pos);
	}
}
void LevelDraw() {
	for (const auto& i : lvldata) {
		for (const auto& j : i.data) {
			rTexture.draw(j);
		}
	}
}