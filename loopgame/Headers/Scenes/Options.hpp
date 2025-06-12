#pragma once
#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <SFML/Graphics.hpp>

extern int musicvolume;
extern int soundvolume;

extern bool musicleftcanpress;
extern bool musicrightcanpress;
extern bool soundleftcanpress;
extern bool soundrightcanpress;
extern bool exitoptionscanpress;

extern sf::Texture optionsbgtexture;
extern sf::Sprite  optionsbg;
extern sf::Texture musicoptionstexture;
extern sf::Sprite  musicoptions;
extern sf::Texture musiclefttexture;
extern sf::Sprite  musicleft;
extern sf::Texture musicrighttexture;
extern sf::Sprite  musicright;
extern sf::Texture soundoptionstexture;
extern sf::Sprite  soundoptions;
extern sf::Texture soundlefttexture;
extern sf::Sprite  soundleft;
extern sf::Texture soundrighttexture;
extern sf::Sprite  soundright;
extern sf::Texture exitoptionstexture;
extern sf::Sprite  exitoptions;

extern void SetOptionsPos();
extern void ActiveButtonOptions();
extern void DrawOptions();

#endif