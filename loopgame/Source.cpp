#include <SFML/Graphics.hpp>

std::vector<sf::Sprite> grass;
std::vector<sf::Sprite> blockorange;

void setHitbox(sf::FloatRect& hitbox, const sf::FloatRect& Sethitbox) {
	hitbox = Sethitbox;
}
sf::FloatRect getGlobalHitbox(const sf::FloatRect& hitbox, const sf::Vector2f& pos) {
	return sf::FloatRect({ pos.x + hitbox.position.x, pos.y + hitbox.position.y }, { hitbox.size.x, hitbox.size.y });
}
sf::FloatRect getGlobalHitbox(const sf::FloatRect& hitbox, const sf::Sprite& sprite) {
	return sprite.getTransform().transformRect(hitbox);
}
bool isCollide(const sf::FloatRect& hitbox, const sf::Sprite& sprite, const sf::FloatRect& other) {
	return bool(getGlobalHitbox(hitbox, sprite).findIntersection(other));
}
void marioCollisionFoot(sf::Sprite& mario, const sf::FloatRect& other) {
	sf::FloatRect block({ 0, 0 }, { 32, 32 });
	bool flag = false;
	for (const auto& i : grass) {
		if (isCollide(other, mario, getGlobalHitbox(block, i))) {
			flag = true;
			break;
		}
	}
	for (const auto& i : blockorange) {
		if (isCollide(other, mario, getGlobalHitbox(block, i))) {
			flag = true;
			break;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
	{
		flag = true;
		mario.move({ 0.f, -5.0f });
	}

	if (!flag) {
		mario.move({ 0.0f, 10.0f });
	}
}
int main()
{
	float time = 0;

	sf::RenderWindow window(sf::VideoMode({ 640, 480 }), "Mario Runner!");
	sf::Texture tileset("Resources/tileset.png");
	sf::Texture mariotexture("Resources/SmallMario.png");

	sf::FloatRect mariofoot({ 1,28 }, { 22,3 });

	window.setFramerateLimit(50);
	for (int i = 0; i < 6; ++i) {
		blockorange.push_back(sf::Sprite(tileset, sf::IntRect({ 0, 64 }, { 32, 32 })));
		blockorange.back().setPosition(sf::Vector2f({ i * 32.0f,384.0f }));
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

	sf::Sprite mario(mariotexture);
	mario.setPosition({ 32, 128 });

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is < sf::Event::KeyReleased>()) {
				time = 0;
			}
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			// left key is pressed: move our character
			time += 0.5;
			if (time < 7.5) {
				mario.move({ -time, 0.f });
			}
			else {
				mario.move({ -7.5f, 0.f });
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			// right key is pressed: move our character
			time += 0.5;
			if (time < 7.5) {
				mario.move({ time, 0.f });
			}
			else {
				mario.move({ 7.5f, 0.f });
			}
		}

		marioCollisionFoot(mario, mariofoot);

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