#pragma once
#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include "GameClass.hpp"
#include "Level.hpp"
extern sf::Texture PiranhaGroundTexture;
extern sf::Texture GoombaTexture;

extern sf::FloatRect goombafoot;
extern sf::FloatRect goombaleft;
extern sf::FloatRect goombaright;

extern void AddPiranhaGround(Level& lvl, float x, float y);
extern void PiranhaGroundAnimationInit();
extern void CheckPiranhaGroundCollision();
extern void AddGoomba(Level& lvl, float x, float y);
extern void GoombaAnimationInit();
extern void CheckGoombaCollision();
extern void GoombaMovement(float dt);
extern void GoombaVerticleUpdate(float dt);
extern void GoombaHorizonUpdate(float dt);

extern void DrawEnemy();
#endif