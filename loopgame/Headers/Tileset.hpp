#pragma once
#ifndef TILESET_HPP
#define TILESET_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "GameClass.hpp"

extern std::vector<sf::Sprite> obstacles;

extern sf::Texture tileset;

extern void addObstacleBlock(Level& lvl, float x, float y, int textureX, int textureY);

#endif