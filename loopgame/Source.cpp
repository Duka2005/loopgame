#include <SFML/Graphics.hpp>
#include "Headers/Mario.hpp"
#include "Headers/Tileset.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 640, 480 }), "Mario Runner!");

	SetMarioPosition(32, 128);

	sf::FloatRect mariofoot({ 1,28 }, { 22,3 });
	sf::FloatRect marioleft({ -1,1 }, { 2,27 });
	sf::FloatRect marioright({ 21,1 }, { 2,27 });

	window.setFramerateLimit(50);
	for (int i = 0; i < 6; ++i) {
		blockorange.push_back(sf::Sprite(tileset, sf::IntRect({ 0, 64 }, { 32, 32 })));
		blockorange.back().setPosition(sf::Vector2f({ 128 + i * 32.0f,384.0f }));
	}
	grass.push_back(sf::Sprite(tileset, sf::IntRect({ 0, 0 }, { 32, 32 })));
	grass.back().setPosition({ 0,416 });
	grass.push_back(sf::Sprite(tileset, sf::IntRect({ 0, 32 }, { 32, 32 })));
	grass.back().setPosition({ 0,448 });
	for (int i = 0; i < 18; ++i) {
		grass.push_back(sf::Sprite(tileset, sf::IntRect({ 32, 0 }, { 32, 32 })));
		grass.back().setPosition(sf::Vector2f({ 32.0f + i * 32.0f,416.0f }));
		grass.push_back(sf::Sprite(tileset, sf::IntRect({ 32, 32 }, { 32, 32 })));
		grass.back().setPosition(sf::Vector2f({ 32.0f + i * 32.0f,448.0f }));
	}
	grass.push_back(sf::Sprite(tileset, sf::IntRect({ 64, 0 }, { 32, 32 })));
	grass.back().setPosition(sf::Vector2f({ 32.0f + 18 * 32.0f,416.0f }));
	grass.push_back(sf::Sprite(tileset, sf::IntRect({ 64, 32 }, { 32, 32 })));
	grass.back().setPosition(sf::Vector2f({ 32.0f + 18 * 32.0f,448.0f }));

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		MarioMovement();

		marioCollisionFoot(mario, mariofoot);
		marioCollisionLeft(mario, marioleft);
		marioCollisionRight(mario, marioright);

		window.clear();
		for (const auto& i : grass) {
			window.draw(i);
		}
		for (const auto& i : blockorange) {
			window.draw(i);
		}
		window.draw(mario);
		window.display();
	}
}