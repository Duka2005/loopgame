#pragma once
#ifndef ENEMYDEATH_HPP
#define ENEMYDEATH_HPP

extern sf::Texture GoombaDeathTexture;

extern sf::FloatRect goombadeathfoot;

extern std::vector<sf::Sprite> GoombaDeathList;
extern std::vector<float> GoombaDeathYVeloList;

extern void AddGoombaDeath(float x, float y);
extern void GoombaDeathVerticleUpdate(float dt);
extern void DrawGoombaDeath();
extern void DeleteGoombaDeath(const float x, const float y);
extern void TimeVisibleGoombaDeath();
#endif