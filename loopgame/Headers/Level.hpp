#pragma once
#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Level {
public:
	std::vector<sf::Sprite> data{};
	std::vector<sf::Vector2f> origin_pos{};
	std::vector<sf::Sprite> piranha_ground_data{};
	std::vector<sf::Vector2f> piranha_ground_origin_pos{};
	int pos = 0;

	void UpdateTilePosition();
	void UpdatePiranhaGroundPosition();
};
extern std::vector<Level> lvldata;
extern void LevelInit();
extern void LevelDraw();
extern void CheckLevelAvaliable();
extern void LevelUpdatePos();
#endif