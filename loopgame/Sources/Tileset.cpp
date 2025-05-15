#include <SFML/Graphics.hpp>
#include "../Headers/Tileset.hpp"
#include "../Headers/Level.hpp"

void addObstacleBlock(Level& lvl, float x, float y, int textureX, int textureY) {
	lvl.data.push_back(sf::Sprite(tileset, sf::IntRect({ textureX, textureY }, { 32, 32 })));
	lvl.origin_pos.push_back(sf::Vector2f({ x ,y }));
}

sf::Texture tileset("Resources/Image/tileset.png");