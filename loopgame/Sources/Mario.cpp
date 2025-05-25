#include <SFML/Graphics.hpp>
#include "../Headers/Mario.hpp"
#include "../Headers/Tileset.hpp"
#include "../Headers/Window.hpp"
#include "../Headers/Sound.hpp"
#include "../Headers/LocalAnimationManager.hpp"
#include "../Headers/Level.hpp"

#include <iostream>

sf::Clock MarioDeathClock;

sf::Texture mariotexture("Resources/Image/SmallMario.png");
sf::Sprite mario(mariotexture);

sf::Texture mariodeathtexture("Resources/Image/Death/mario_death.png");
sf::Sprite mariodeath(mariodeathtexture);

LocalAnimationManager MarioAnimation;

bool CanMarioControl = true;
bool MarioCurrentFalling = true;
bool MarioCurrentTouchBlockLeft = false;
bool MarioCurrentTouchBlockRight = false;
bool FirstMarioDirection = false;
bool PreJump = false;
bool Holding;
bool OverSpeed = false;
bool MarioDirection = FirstMarioDirection;
float Xvelocity = 0.0f;
float Yvelocity = 0.0f;
float mario_speed;
int MarioState = 0;
int lastMarioState = -1;
bool isactive = false;
bool processdeath = false;

sf::FloatRect mariofoot({ 1 + 4 ,29 }, { 22,2 });
sf::FloatRect marioleft({ -1 + 4,1 }, { 2,27 });
sf::FloatRect marioright({ 22 + 4,1 }, { 2,27 });
sf::FloatRect mariohead({ 1 + 4,-1 }, { 22,2 });
sf::FloatRect mariomain({ 0 + 4,0 }, { 23,29 });

void SetMarioPosition(float x, float y) {
	mario.setPosition({ x, y });
}

void setHitbox(sf::FloatRect& hitbox, const sf::FloatRect& Sethitbox) {
	hitbox = Sethitbox;
}
sf::FloatRect getGlobalHitbox(const sf::FloatRect& hitbox, const sf::Vector2f& pos, const sf::Vector2f& origin) {
	return sf::FloatRect({ pos.x + hitbox.position.x - origin.x, pos.y + hitbox.position.y - origin.y }, { hitbox.size.x, hitbox.size.y });
}
sf::FloatRect getGlobalHitbox(const sf::FloatRect& hitbox, const sf::Sprite& sprite) {
	return sprite.getTransform().transformRect(hitbox);
}
bool isCollide(const sf::FloatRect& hitbox, const sf::Sprite& sprite, const sf::FloatRect& other) {
	return bool(getGlobalHitbox(hitbox, sprite).findIntersection(other));
}
bool isCollide(const sf::FloatRect& hitbox, const sf::FloatRect& other) {
	return static_cast<bool>(hitbox.findIntersection(other));
}

sf::Vector2f CheckMarioCollision(sf::Sprite& mario, const sf::FloatRect& other) {
	sf::FloatRect block({ 0, 0 }, { 32, 32 });
	sf::Vector2f pos({ -1, -1 });
	for (const auto& i : lvldata) {
		for (const auto& j : i.data) {
			if (isCollide(other, mario, getGlobalHitbox(block, j))) {
				pos = { j.getPosition().x, j.getPosition().y };
				break;
			}
		}
	}
	return pos;
}

void MarioVerticleUpdate(float dt) {
	sf::FloatRect block({ 0, 0 }, { 32, 32 });
	if (!processdeath) {
		Yvelocity += (Yvelocity < 10.0f ? 1.0f * dt : 0.0f);
		if (Yvelocity > 10.0f) Yvelocity = 10.0f;
		mario.move({ 0.f, Yvelocity * dt });
	}

	sf::Vector2f pos = CheckMarioCollision(mario, mariofoot);

	if (pos.y != -1) {
		MarioCurrentFalling = false;
		mario.setPosition({ mario.getPosition().x, pos.y - 31.0f + 28.0f });
		Yvelocity = 0.0f;
	}
	else MarioCurrentFalling = true;

	pos = CheckMarioCollision(mario, mariohead);
	if (pos.y != -1) {
		mario.setPosition({ mario.getPosition().x, pos.y + 33.0f + 28.0f });
		Yvelocity = 0.0f;
	}
}
void MarioHorizonUpdate(float dt) {
	sf::FloatRect block({ 0, 0 }, { 32, 32 });

	// kiem tra ben phai
	sf::Vector2f pos = CheckMarioCollision(mario, marioright);
	if (pos.x != -1) {
		MarioCurrentTouchBlockRight = true;
		mario.setPosition({ pos.x - 24.0f + 7.0f, mario.getPosition().y });
		Xvelocity = 0.0f;
	}
	else MarioCurrentTouchBlockRight = false;

	// kiem tra ben trai
	pos = CheckMarioCollision(mario, marioleft);
	if (pos.x != -1) {
		MarioCurrentTouchBlockLeft = true;
		mario.setPosition({ pos.x + 33.0f + 7.0f, mario.getPosition().y });
		Xvelocity = 0.0f;
	}
	else MarioCurrentTouchBlockLeft = false;

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X) && Xvelocity > 4.475f) {
		OverSpeed = true;
	}
	if (Xvelocity > mario_speed && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
		if (OverSpeed) {
			Xvelocity -= 0.125f * dt;
			if (Xvelocity <= mario_speed) OverSpeed = false;
		}
		else Xvelocity = mario_speed;
	}
	if (Xvelocity > 7.5f && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) Xvelocity = 7.5f;
}
void MarioMovement(float dt) {
	if (CanMarioControl) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && window.hasFocus())
		{
			// quan tinh cua nhan vat
			if (Xvelocity == 0.0f) MarioDirection = true;
			else if (!MarioDirection) {
				Xvelocity -= (Xvelocity <= 0.0f ? 0.0f : 0.375f * dt);
				mario.move({ Xvelocity * dt, 0.f });
			}
			// init
			if (Xvelocity < 1.0f && MarioDirection) Xvelocity = 1.0f;
			// nhan vat di chuyen khi nhan phim Left
			if (MarioDirection && !MarioCurrentTouchBlockRight) {
				Xvelocity += (Xvelocity > mario_speed ? 0.0f : 0.125f * dt);
				mario.move({ -Xvelocity * dt, 0.f });
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && window.hasFocus())
		{
			// quan tinh cua nhan vat
			if (Xvelocity == 0.0f) MarioDirection = false;
			else if (MarioDirection) {
				Xvelocity -= (Xvelocity <= 0.0f ? 0.0f : 0.375f * dt);
				mario.move({ -Xvelocity * dt, 0.f });
			}
			// init
			if (Xvelocity < 1.0f && !MarioDirection) Xvelocity = 1.0f;
			// nhan vat di chuyen khi nhan phim Right
			if (!MarioDirection && !MarioCurrentTouchBlockLeft) {
				Xvelocity += (Xvelocity > mario_speed ? 0.0f : 0.125f * dt);
				mario.move({ Xvelocity * dt, 0.f });
			}
		}
		else if ((!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))) {
			Xvelocity -= (Xvelocity <= 0.0f ? 0.0f : 0.125f * dt);
			if (!MarioDirection) mario.move({ Xvelocity * dt, 0.0f });
			else mario.move({ -Xvelocity * dt, 0.0f });
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z) && !MarioCurrentFalling && window.hasFocus()) {
			if (!PreJump && !Holding) {
				jump.play();
				Yvelocity = -14.0f;
				MarioCurrentFalling = true;
				Holding = true;
			}
			else if (PreJump) {
				jump.play();
				Yvelocity = -14.0f;
				MarioCurrentFalling = true;
				PreJump = false;
				Holding = true;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z) && window.hasFocus()) {
			if (Xvelocity < 5.0f && Yvelocity < 0.0f) Yvelocity -= 0.4f * dt;
			if (Xvelocity >= 5.0f && Yvelocity < 0.0f) Yvelocity -= 0.5f * dt;
			if (Yvelocity >= 0.0f && !Holding) PreJump = true;
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z) && window.hasFocus()) Holding = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X) && window.hasFocus()) mario_speed = 7.5f;
		else mario_speed = 4.375f;
		if (!MarioCurrentFalling && PreJump) PreJump = false;
		if (Xvelocity < 0.0f) Xvelocity = 0.0f;
	}
}

//kiem tra khi nhan vat den dau va cuoi man hinh
void MoveFromOffset() {
	if (mario.getPosition().x <= initx - 320.0f + 10.0f) {
		mario.setPosition({ initx - 320.0f + 10.0f, mario.getPosition().y });
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) Xvelocity = 0.0f;
		//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && Xvelocity <= 3.0f) mario.setPosition({ initx - 320.0f + 11.0f + (4.0f - Xvelocity), mario.getPosition().y});
	}
	else if (mario.getPosition().x >= initx + 320.0f - 18.0f) {
		mario.setPosition({ initx + 320.0f - 18.0f, mario.getPosition().y });
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) Xvelocity = 0.0f;
	}
}

void MarioInit() {
	mario.setOrigin({ 11, 28 });
	mariodeath.setOrigin({ 11, 28 });
	MarioDeathClock.reset();
}

// animation cua nhan vat
void updateAnimation() {
	int ypos = (!MarioDirection) ? 0 : 1;
	if (CanMarioControl) {
		if (MarioCurrentFalling) {
			MarioState = 2;
			if (lastMarioState != MarioState && MarioState != 4) {
				MarioAnimation.setAnimation(3, 3, 31, 31, ypos, 100);
				lastMarioState = MarioState;
			}
			MarioAnimation.setYPos(ypos);
			MarioAnimation.update(mario);
		}
		else if (Yvelocity == 0.0f && !(!MarioCurrentFalling && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))) {
			if (Xvelocity == 0.0f) {
				MarioState = 0;
				if (lastMarioState != MarioState && MarioState != 4) {
					MarioAnimation.setAnimation(2, 2, 31, 31, ypos, 0);
					lastMarioState = MarioState;
				}
				MarioAnimation.setYPos(ypos);
				MarioAnimation.update(mario);
			}
			else {
				MarioState = 1;
				if (lastMarioState != MarioState && MarioState != 4) {
					MarioAnimation.setAnimation(0, 2, 31, 31, ypos);
					lastMarioState = MarioState;
				}
				MarioAnimation.setYPos(ypos);
				MarioAnimation.setFrequency(std::max(12.0f, std::min(Xvelocity * 6.0f, 45.0f)));
				MarioAnimation.update(mario);
			}
		}
	}
}
void MarioDeathUpdate(float dt) {
	if (isactive) {
		mariodeath.setPosition(mario.getPosition());
		Yvelocity = -10.0f;
		isactive = false;
		processdeath = true;
	}
	if (processdeath) {
		if (MarioDeathClock.getElapsedTime().asSeconds() >= 0.5f) {
			Yvelocity += (Yvelocity < 10.0f ? 0.3f * dt : 0.0f);
			if (Yvelocity > 10.0f) Yvelocity = 10.0f;
			mariodeath.move({ 0.0f, Yvelocity * dt });
		}
	}
}

void MarioDeath() {
	music.stop();
	CanMarioControl = false;
	isactive = true;
	death.play();
	MarioDeathClock.start();
}