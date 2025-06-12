#pragma once
#ifndef WINDOW_HPP
#define WINDOW_HPP

extern bool GAME_PAUSE;

extern sf::Clock Gameclock;

extern sf::RenderWindow window;
extern sf::RenderTexture rTexture;

extern sf::View viewwin;
extern sf::View view;

extern int CurrentScene;

extern void ViewInit();
extern void setView(float dt);
extern void updateView();
extern bool isOutScreenRight(const sf::Vector2f& pos, const sf::Vector2f& offset);

extern float initx;
extern float prev_initx;
extern float speedtime;

extern float stage1;
extern float stage2;
extern float stage3;
extern float prev_speedtime;

extern void checktimeupspeed();
extern float ViewXOff, ViewYOff;

#endif