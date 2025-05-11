#include <SFML/Graphics.hpp>
#include "../Headers/Tileset.hpp"
#include "../Headers/Level.hpp"

std::vector<sf::Sprite> obstacles;

void addObstacleBlock(Level& lvl, float x, float y, int textureX, int textureY) {
	lvl.data.push_back(sf::Sprite(tileset, sf::IntRect({ textureX, textureY }, { 32, 32 })));
	lvl.data.back().setPosition(sf::Vector2f({ x ,y }));
}

sf::Texture tileset("Resources/Image/tileset.png");