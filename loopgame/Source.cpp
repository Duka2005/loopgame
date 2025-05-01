#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 640, 480 }), "Mario Runner!");
	sf::Texture grass1("Resources/1.png", false, sf::IntRect({ 0, 0 }, { 32, 32 }));
	sf::Sprite grass(grass1);

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>())
				window.close();
		}
		grass.setPosition({ 0,416 });
		window.clear();
		window.draw(grass);
		window.display();
	}
}