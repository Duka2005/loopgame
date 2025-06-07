#pragma once

#ifndef FONT_HPP
#define FONT_HPP

#include <vector>
#include <SFML/Graphics.hpp>

extern std::string FontString;
extern void SetFontSize(int TextSizeX, int TextSizeY, int sizeX, int sizeY);
extern int GetFontIndex(char c);
extern sf::IntRect GetFontTexture(char c);
extern int FontSizeX;
extern int FontSizeY;

#endif // FONT_HPP