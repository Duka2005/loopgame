#pragma once
#ifndef TOTALSCORE_HPP
#define TOTALSCORE_HPP

#include <SFML/Graphics.hpp>

extern sf::Texture totalscorebgtexture;
extern sf::Sprite  totalscorebg;
extern sf::Texture mainmenutotalscoretexture;
extern sf::Sprite  mainmenutotalscore;
extern sf::Texture playagaintexture;
extern sf::Sprite  playagain;
extern sf::Texture gameovertexture;
extern sf::Sprite  gameover;

extern void SetTotalScorePos();
extern void ActiveTotalScore();
extern void TotalScoreDraw();

#endif