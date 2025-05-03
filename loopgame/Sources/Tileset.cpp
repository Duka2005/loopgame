#include <SFML/Graphics.hpp>
#include "../Headers/Tileset.hpp"

std::vector<sf::Sprite> obstacles;

void addObstacleBlock(float x, float y, int textureX, int textureY) {
	obstacles.push_back(sf::Sprite(tileset, sf::IntRect({ textureX, textureY }, { 32, 32 })));
	obstacles.back().setPosition(sf::Vector2f({ x ,y }));
}

sf::Texture tileset("Resources/Image/tileset.png");