#include <SFML/Graphics.hpp>
#include "../Headers/BackgroundColor.hpp"
#include "../Headers/Window.hpp"
#include "../Headers/Mario.hpp"

sf::VertexArray Backgroundcolor = sf::VertexArray(sf::PrimitiveType::TriangleStrip,4);

//set position background
void BgColorInitPos() {
	Backgroundcolor[0].position = sf::Vector2f(-320.f + initx, 0.f);
	Backgroundcolor[1].position = sf::Vector2f(320.f + initx, 0.f);
	Backgroundcolor[2].position = sf::Vector2f(-320.f + initx, 480.f);
	Backgroundcolor[3].position = sf::Vector2f(320.f + initx, 480.f);
}

//set color background
void BgColorInitColor() {
	Backgroundcolor[0].color = sf::Color(51, 51, 255, 255);
	Backgroundcolor[1].color = sf::Color(51, 51, 255, 255);
	Backgroundcolor[2].color = sf::Color(255, 255, 255, 255);
	Backgroundcolor[3].color = sf::Color(255, 255, 255, 255);
}