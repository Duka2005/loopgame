#pragma once
#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Level {
public:
	std::vector<sf::Sprite> data{};
	std::vector<sf::Vector2f> origin_pos{};
	int pos = 0;

	void UpdateTilePosition();
};
extern std::vector<Level> lvldata;
extern void LevelInit();
extern void LevelDraw();
extern void CheckLevelAvaliable();
extern void LevelUpdatePos();
#endif