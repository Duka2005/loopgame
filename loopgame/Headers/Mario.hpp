#pragma once
#ifndef MARIO_HPP
#define MARIO_HPP

extern sf::Clock MarioDeathClock;

extern sf::Texture mariotexture;
extern sf::Sprite mario;
extern sf::Texture mariodeathtexture;
extern sf::Sprite mariodeath;

extern bool CanMarioControl, FirstMarioDirection, MarioDirection, MarioCurrentFalling, isactive, processdeath;
extern float Xvelocity, Yvelocity;

extern sf::FloatRect mariofoot;
extern sf::FloatRect marioleft;
extern sf::FloatRect marioright;
extern sf::FloatRect mariohead;
extern sf::FloatRect mariomain;

extern void MarioMovement(float dt);
extern void SetMarioPosition(float x, float y);
extern void setHitbox(sf::FloatRect& hitbox, const sf::FloatRect& Sethitbox);
extern sf::FloatRect getGlobalHitbox(const sf::FloatRect& hitbox, const sf::Vector2f& pos, const sf::Vector2f& origin);
extern sf::FloatRect getGlobalHitbox(const sf::FloatRect& hitbox, const sf::Sprite& sprite);
extern bool isCollide(const sf::FloatRect& hitbox, const sf::Sprite& sprite, const sf::FloatRect& other);
extern bool isCollide(const sf::FloatRect& hitbox, const sf::FloatRect& other);
extern void MarioVerticleUpdate(float dt);
extern void MarioHorizonUpdate(float dt);
extern void updateAnimation();
extern void MarioDeathUpdate(float dt);
extern void MarioInit();
extern void MoveFromOffset();
extern void MarioStuck();
extern void MarioDeath();

#endif