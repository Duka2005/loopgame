#pragma once
#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "../Headers/Level.hpp"

extern sf::Texture PiranhaGroundTexture;

extern void AddPiranhaGround(Level& lvl, float x, float y);
extern void PiranhaGroundAnimationInit();
extern void DrawPiranhaGround();
extern void CheckPiranhaGroundCollision();

#endif