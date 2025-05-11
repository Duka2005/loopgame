#pragma once
#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Level {
public:
	std::vector<sf::Sprite> data{};
	int pos = 0;
};
extern std::vector<Level> lvldata;
extern void LevelInit();
extern void LevelDraw();
extern void CheckLevelAvaliable();
#endif