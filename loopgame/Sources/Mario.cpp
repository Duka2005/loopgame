#include <SFML/Graphics.hpp>
#include "../Headers/Mario.hpp"
#include "../Headers/Tileset.hpp"
#include "../Headers/Window.hpp"

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

sf::FloatRect mariofoot({ 1,29 }, { 22,2 });
sf::FloatRect marioleft({ -1,1 }, { 2,27 });
sf::FloatRect marioright({ 22,1 }, { 2,27 });

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
void marioCollisionLeft(sf::Sprite& mario, const sf::FloatRect& other) {
	sf::FloatRect block({ 0, 0 }, { 32, 32 });
	bool flag = false;
	for (const auto& i : obstacles) {
		if (isCollide(other, mario, getGlobalHitbox(block, i)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)))) {
			flag = true;
			mario.move({ Xvelocity, 0.f });
			Xvelocity = 0.0f;
			break;
		}
	}
	MarioCurrentTouchBlockLeft = flag;
}
void marioCollisionRight(sf::Sprite& mario, const sf::FloatRect& other) {
	sf::FloatRect block({ 0, 0 }, { 32, 32 });
	bool flag = false;
	for (const auto& i : obstacles) {
		if (isCollide(other, mario, getGlobalHitbox(block, i)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)))) {
			flag = true;
			mario.move({ -Xvelocity, 0.f });
			Xvelocity = 0.0f;
			break;
		}
	}
	MarioCurrentTouchBlockRight = flag;
}
void marioCollisionHead(sf::Sprite& mario, const sf::FloatRect& other) {
	sf::FloatRect block({ 0, 0 }, { 32, 32 });
}

sf::Vector2f CheckMarioCollision(sf::Sprite& mario, const sf::FloatRect& other) {
	sf::FloatRect block({ 0, 0 }, { 32, 32 });
	sf::Vector2f pos({ -1, -1 });
	for (const auto& i : obstacles) {
		if (isCollide(other, mario, getGlobalHitbox(block, i))) {
			pos = { i.getPosition().x, i.getPosition().y };
			break;
		}
	}
	return pos;
}

void MarioVerticleUpdate() {
	sf::FloatRect block({ 0, 0 }, { 32, 32 });

	Yvelocity += (Yvelocity < 10.0f ? 1.0f : 0.0f);
	if (Yvelocity > 10.0f) Yvelocity = 10.0f;
	mario.move({ 0.f, Yvelocity });

	sf::Vector2f pos = CheckMarioCollision(mario, mariofoot);

	if (pos.y != -1) {
		MarioCurrentFalling = false;
		mario.setPosition({ mario.getPosition().x, pos.y - 30.0f });
		Yvelocity = 0.0f;
	}
	else MarioCurrentFalling = true;
}
void MarioHorizonUpdate() {
	sf::FloatRect block({ 0, 0 }, { 32, 32 });

	// kiem tra ben phai
	sf::Vector2f pos = CheckMarioCollision(mario, marioright);
	if (pos.x != -1) {
		MarioCurrentTouchBlockRight = true;
		mario.setPosition({ pos.x - 24.0f, mario.getPosition().y });
		Xvelocity = 0.0f;
	}
	else MarioCurrentTouchBlockRight = false;

	// kiem tra ben trai
	pos = CheckMarioCollision(mario, marioleft);
	if (pos.x != -1) {
		MarioCurrentTouchBlockLeft = true;
		mario.setPosition({ pos.x + 33.0f, mario.getPosition().y });
		Xvelocity = 0.0f;
	}
	else MarioCurrentTouchBlockLeft = false;
}
void MarioMovement() {
	if (CanMarioControl) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && window.hasFocus())
		{
			// quan tinh cua nhan vat
			if (Xvelocity == 0.0f) MarioDirection = true;
			else if (!MarioDirection) {
				Xvelocity -= (Xvelocity <= 0.0f ? 0.0f : 0.375f);
				mario.move({ Xvelocity, 0.f });
			}
			// nhan vat di chuyen khi nhan phim Left
			if (MarioDirection && !MarioCurrentTouchBlockRight) {
				Xvelocity += (Xvelocity > 7.5f ? 0.0f : 0.125f);
				mario.move({ -Xvelocity, 0.f });
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && window.hasFocus())
		{
			// quan tinh cua nhan vat
			if (Xvelocity == 0.0f) MarioDirection = false;
			else if (MarioDirection) {
				Xvelocity -= (Xvelocity <= 0.0f ? 0.0f : 0.375f);
				mario.move({ -Xvelocity, 0.f });
			}
			// nhan vat di chuyen khi nhan phim Right
			if (!MarioDirection && !MarioCurrentTouchBlockLeft) {
				Xvelocity += (Xvelocity > 7.5f ? 0.0f : 0.125f);
				mario.move({ Xvelocity, 0.f });
			}
		}
		else if ((!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))) {
			Xvelocity -= (Xvelocity <= 0.0f ? 0.0f : 0.125f);
			if (!MarioDirection) mario.move({ Xvelocity, 0.0f });
			else mario.move({ -Xvelocity, 0.0f });
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z) && !MarioCurrentFalling) {
			Yvelocity = -13.5f;
			MarioCurrentFalling = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z) && window.hasFocus()) {
			if (Xvelocity < 5.0f && Yvelocity < 0.0f) Yvelocity -= 0.4f;
			if (Xvelocity >= 5.0f && Yvelocity < 0.0f) Yvelocity -= 0.5f;
			//if (Yvelo >= 0.0f && !Holding) PreJump = true;
		}
		if (Xvelocity < 0.0f) Xvelocity = 0.0f;
	}
}