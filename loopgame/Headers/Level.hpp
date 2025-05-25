#pragma once
#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "GameClass.hpp"

extern std::vector<Level> lvldata;
extern void LevelInit();
extern void LevelDraw();
extern void CheckLevelAvaliable();
extern void LevelUpdatePos();
#endif