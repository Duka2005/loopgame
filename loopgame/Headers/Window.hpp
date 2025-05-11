#pragma once
#ifndef WINDOW_HPP
#define WINDOW_HPP

extern sf::RenderWindow window;
extern sf::RenderTexture rTexture;

extern sf::View viewwin;
extern sf::View view;

extern void ViewInit();
extern void setView();

#endif