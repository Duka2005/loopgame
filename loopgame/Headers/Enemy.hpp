#pragma once
#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include "GameClass.hpp"
#include "Level.hpp"
extern sf::Texture PiranhaGroundTexture;
extern sf::Texture GoombaTexture;
extern sf::Texture SpinyTexture;

extern sf::FloatRect goombafoot;
extern sf::FloatRect goombaleft;
extern sf::FloatRect goombaright;

extern sf::FloatRect spinyfoot;
extern sf::FloatRect spinyleft;
extern sf::FloatRect spinyright;

extern void AddPiranhaGround(Level& lvl, float x, float y);
extern void PiranhaGroundAnimationInit();
extern void CheckPiranhaGroundCollision();

extern void AddGoomba(Level& lvl, float x, float y);
extern void GoombaAnimationInit();
extern void CheckGoombaCollision();
extern void DeleteGoomba(const float x, const float y);
extern void GoombaMovement(float dt);
extern void GoombaVerticleUpdate(float dt);
extern void GoombaHorizonUpdate(float dt);
extern void GoombaStatusUpdate();

extern void AddSpiny(Level& lvl, float x, float y);
extern void CheckSpinyCollision();
extern void SpinyMovement(float dt);
extern void SpinyVerticleUpdate(float dt);
extern void SpinyHorizonUpdate(float dt);
extern void SpinyStatusUpdate();

extern void DrawEnemy();
#endif