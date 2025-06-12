#pragma once
#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <SFML/Graphics.hpp>

extern float started;
extern bool BlackBackgroundTrigger;

extern float mouse_x, mouse_y;

extern sf::Cursor cursorhand;
extern sf::Cursor cursorarrow;

extern sf::Texture backgroundmainmenutexture;
extern sf::Sprite backgroundmainmenu;
extern sf::Texture mariorunnertexture;
extern sf::Sprite mariorunner;
extern sf::Texture boxtexture;
extern sf::Sprite boxmainmenu;
extern sf::Texture starttexture;
extern sf::Sprite  startbutton;
extern sf::Texture optionstexture;
extern sf::Sprite  optionsbutton;
extern sf::Texture quittexture;
extern sf::Sprite  quitbutton;

extern sf::VertexArray blackscreen1;

extern void SetMainmenuPos();
extern void BlackScreenProcess(bool& process, const float dt, float& started, sf::VertexArray& blackscreen1);
extern void ActiveButtonMainMenu();
extern void DrawMainMenu();

#endif