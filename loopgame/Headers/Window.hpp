#pragma once
#ifndef WINDOW_HPP
#define WINDOW_HPP

extern sf::RenderWindow window;
extern sf::RenderTexture rTexture;

extern sf::View viewwin;
extern sf::View view;

extern void ViewInit();
extern void setView(float dt);
extern void updateView();

extern float initx;
extern float speedtime;

#endif