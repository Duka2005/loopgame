#include <SFML/Graphics.hpp>
#include "../Headers/Mario.hpp"
#include "../Headers/Tileset.hpp"

#include <iostream>

sf::Texture mariotexture("Resources/SmallMario.png");
sf::Sprite mario(mariotexture);

bool CanMarioControl = true;
bool MarioCurrentFalling = true;
bool MarioCurrentTouchBlockLeft = false;
bool MarioCurrentTouchBlockRight = false;
bool FirstMarioDirection = false;
bool MarioDirection = FirstMarioDirection;
float Xvelocity = 0.0f;
float Yvelocity = 0.0f;

void SetMarioPosition(float x, float y) {
	mario.setPosition({ x, y });
}

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

	Yvelocity += 0.5f;
	mario.move({ 0.f, Yvelocity });

	for (const auto& i : grass) {
		if (isCollide(other, mario, getGlobalHitbox(block, i))) {
			MarioCurrentFalling = false;
			mario.move({ 0.f, -Yvelocity });
			Yvelocity = 0.0f;
			break;
		}
	}
	for (const auto& i : blockorange) {
		if (isCollide(other, mario, getGlobalHitbox(block, i))) {
			MarioCurrentFalling = false;
			mario.move({ 0.f, -Yvelocity });
			Yvelocity = 0.0f;
			break;
		}
	}
}

void marioCollisionLeft(sf::Sprite& mario, const sf::FloatRect& other) {
	sf::FloatRect block({ 0, 0 }, { 32, 32 });
	bool flag = false;
	for (const auto& i : blockorange) {
		if (isCollide(other, mario, getGlobalHitbox(block, i)) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
			flag = true;
			Xvelocity = 0.0f;
			mario.move({ Xvelocity, 0.f });
			break;
		}
	}
	MarioCurrentTouchBlockLeft = flag;
}
void marioCollisionRight(sf::Sprite& mario, const sf::FloatRect& other) {
	sf::FloatRect block({ 0, 0 }, { 32, 32 });
	bool flag = false;
	for (const auto& i : blockorange) {
		if (isCollide(other, mario, getGlobalHitbox(block, i)) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
			flag = true;
			Xvelocity = 0.0f;
			mario.move({ Xvelocity, 0.f });
			break;
		}
	}
	MarioCurrentTouchBlockRight = flag;
}
void marioCollisionHead(sf::Sprite& mario, const sf::FloatRect& other) {
	sf::FloatRect block({ 0, 0 }, { 32, 32 });
}

void MarioMovement() {
	if (CanMarioControl) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			if (!MarioDirection) {
				MarioDirection = true;
				Xvelocity = 1.0f;
			}
			// left key is pressed: move our character
			if (MarioDirection && !MarioCurrentTouchBlockLeft) {
				Xvelocity += (Xvelocity > 7.5f ? 0.0f : 0.125f);
				mario.move({ -Xvelocity, 0.f });
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			if (MarioDirection) {
				MarioDirection = false;
				Xvelocity = 1.0f;
			}
			// right key is pressed: move our character
			if (!MarioDirection && !MarioCurrentTouchBlockRight) {
				Xvelocity += (Xvelocity > 7.5f ? 0.0f : 0.125f);
				mario.move({ Xvelocity, 0.f });
			}
		}
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
			Xvelocity = 0.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z) && !MarioCurrentFalling) {
			Yvelocity = -13.5f;
			MarioCurrentFalling = true;
		}
	}
}