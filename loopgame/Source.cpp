#include <SFML/Graphics.hpp>
#include "Headers/Mario.hpp"
#include "Headers/Tileset.hpp"
#include "Headers/Window.hpp"

int main()
{
	sf::RenderTexture rTexture({ 640, 480 });

	SetMarioPosition(32, 128);

	window.setFramerateLimit(50);
	for (int i = 0; i < 6; ++i) {
		obstacles.push_back(sf::Sprite(tileset, sf::IntRect({ 0, 64 }, { 32, 32 })));
		obstacles.back().setPosition(sf::Vector2f({ 128 + i * 32.0f,384.0f }));
	}
	obstacles.push_back(sf::Sprite(tileset, sf::IntRect({ 0, 64 }, { 32, 32 })));
	obstacles.back().setPosition(sf::Vector2f({ 128.0f ,352.0f }));
	obstacles.push_back(sf::Sprite(tileset, sf::IntRect({ 0, 64 }, { 32, 32 })));
	obstacles.back().setPosition(sf::Vector2f({ 128.0f ,320.0f }));
	obstacles.push_back(sf::Sprite(tileset, sf::IntRect({ 0, 64 }, { 32, 32 })));
	obstacles.back().setPosition(sf::Vector2f({ 128.0f ,288.0f }));
	obstacles.push_back(sf::Sprite(tileset, sf::IntRect({ 0, 64 }, { 32, 32 })));
	obstacles.back().setPosition(sf::Vector2f({ 128.0f + 64.0f ,352.0f }));
	obstacles.push_back(sf::Sprite(tileset, sf::IntRect({ 0, 0 }, { 32, 32 })));
	obstacles.back().setPosition({ 0,416 });
	obstacles.push_back(sf::Sprite(tileset, sf::IntRect({ 0, 32 }, { 32, 32 })));
	obstacles.back().setPosition({ 0,448 });
	for (int i = 0; i < 18; ++i) {
		obstacles.push_back(sf::Sprite(tileset, sf::IntRect({ 32, 0 }, { 32, 32 })));
		obstacles.back().setPosition(sf::Vector2f({ 32.0f + i * 32.0f,416.0f }));
		obstacles.push_back(sf::Sprite(tileset, sf::IntRect({ 32, 32 }, { 32, 32 })));
		obstacles.back().setPosition(sf::Vector2f({ 32.0f + i * 32.0f,448.0f }));
	}
	obstacles.push_back(sf::Sprite(tileset, sf::IntRect({ 64, 0 }, { 32, 32 })));
	obstacles.back().setPosition(sf::Vector2f({ 32.0f + 18 * 32.0f,416.0f }));
	obstacles.push_back(sf::Sprite(tileset, sf::IntRect({ 64, 32 }, { 32, 32 })));
	obstacles.back().setPosition(sf::Vector2f({ 32.0f + 18 * 32.0f,448.0f }));

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		MarioMovement();

		MarioHorizonUpdate();
		MarioVerticleUpdate();
		//marioCollisionLeft(mario, marioleft);
		//marioCollisionRight(mario, marioright);

		rTexture.clear();
		for (const auto& i : obstacles) {
			rTexture.draw(i);
		}
		rTexture.draw(mario);
		rTexture.display();
		window.clear();
		window.draw(sf::Sprite(rTexture.getTexture()));
		window.display();
	}
}