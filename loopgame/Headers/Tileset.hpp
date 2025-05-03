#pragma once
#ifndef TILESET_HPP
#define TILESET_HPP

extern std::vector<sf::Sprite> obstacles;

extern sf::Texture tileset;

extern void addObstacleBlock(float x, float y, int textureX, int textureY);

#endif