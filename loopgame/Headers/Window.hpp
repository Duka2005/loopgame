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
extern bool isOutScreenRight(const sf::Vector2f& pos, const sf::Vector2f& offset);

extern float initx;
extern float speedtime;

#endif