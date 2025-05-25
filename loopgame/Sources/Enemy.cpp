#include <SFML/Graphics.hpp>
#include "../Headers/GameClass.hpp"
#include "../Headers/Enemy.hpp"
#include "../Headers/LocalAnimationManager.hpp"
#include "../Headers/Mario.hpp"
#include "../Headers/Level.hpp"
#include "../Headers/Window.hpp"
#include <vector>
#include <iostream>
sf::Texture PiranhaGroundTexture("Resources/Image/Enemy/PiranhaGround.png");
sf::Texture GoombaTexture("Resources/Image/Enemy/Goomba.png");

LocalAnimationManager PiranhaGroundAnimation;
LocalAnimationManager GoombaAnimation;

sf::FloatRect goombafoot({ 1 ,32 }, { 30,2 });
sf::FloatRect goombaleft({ -1,1 }, { 2,30 });
sf::FloatRect goombaright({ 30,1 }, { 2,30 });

//Piranha Ground
void AddPiranhaGround(Level& lvl, float x, float y) {
	lvl.piranha_ground_data.push_back(sf::Sprite(PiranhaGroundTexture));
	lvl.piranha_ground_origin_pos.push_back(sf::Vector2f({ x ,y }));
}

void PiranhaGroundAnimationInit() {
	PiranhaGroundAnimation.setAnimation(0, 3, 32, 32, 0, 22);
}

void CheckPiranhaGroundCollision() {
	sf::FloatRect PiranhaGroundHitBox({ 0, 0 }, { 32, 32 });
	if (processdeath) return;
	for (const auto& i : lvldata) {
		for (const auto& j : i.piranha_ground_data) {
			if (isCollide(mariomain, mario, getGlobalHitbox(PiranhaGroundHitBox, j))) {
				MarioDeath();
				break;
			}
		}
	}
}

//Goomba
float GoombaXvelocity = 0.0f;
float GoombaYvelocity = 0.0f;
float GoombaSpeed;
bool FirstGoombaDirection = true;
bool GoombaDirection = FirstGoombaDirection;

void AddGoomba(Level& lvl, float x, float y) {
	lvl.goomba_data.push_back(GoombaEnemy(GoombaTexture));
	lvl.goomba_origin_pos.push_back(sf::Vector2f({ x,y }));
}

void GoombaAnimationInit() {
	GoombaAnimation.setAnimation(0, 1, 31, 32, 0, 11);
}

void CheckGoombaCollision() {
	sf::FloatRect GoombaHitBox({ 0, 0 }, { 31, 32 });
	if (processdeath) return;
	for (const auto& i : lvldata) {
		for (const auto& j : i.goomba_data) {
			if (isCollide(mariomain, mario, getGlobalHitbox(GoombaHitBox, j.getPosition(), j.getOrigin()))) {
				MarioDeath();
				break;
			}
		}
	}
}

void GoombaMovement(float dt) {
	for (auto& i : lvldata) {
		for (unsigned int j = 0; j < i.goomba_data.size(); ++j) {
			if (i.goomba_data[j].getGoombaXvelocity() < 1.0f && i.goomba_data[j].getGoombaDirection()) i.goomba_data[j].setGoombaXvelocity(1.0f);

			if (i.goomba_data[j].getGoombaDirection()) i.goomba_origin_pos[j] = { i.goomba_origin_pos[j].x - i.goomba_data[j].getGoombaXvelocity() * dt, i.goomba_origin_pos[j].y };
			if (!i.goomba_data[j].getGoombaDirection()) i.goomba_origin_pos[j] = { i.goomba_origin_pos[j].x + i.goomba_data[j].getGoombaXvelocity() * dt, i.goomba_origin_pos[j].y };
		}
		
	}
}

void GoombaVerticleUpdate(float dt) {
	sf::FloatRect block({ 0, 0 }, { 32, 32 });
	sf::Vector2f pos({ -1, -1 });
	for (auto& i : lvldata) {
		for (unsigned int j = 0; j < i.goomba_data.size(); ++j) {
			i.goomba_data[j].setGoombaYvelocity(i.goomba_data[j].getGoombaYvelocity() + (i.goomba_data[j].getGoombaYvelocity() < 10.0f ? 1.0f * dt * 0.3f : 0.0f));
			if (i.goomba_data[j].getGoombaYvelocity() > 10.0f) i.goomba_data[j].setGoombaYvelocity(10.0f);
			i.goomba_origin_pos[j] = { i.goomba_origin_pos[j].x, i.goomba_origin_pos[j].y + i.goomba_data[j].getGoombaYvelocity() * dt };

			const sf::FloatRect goombaGlobal = getGlobalHitbox(goombafoot, sf::Vector2f({ i.goomba_origin_pos[j].x + i.pos * 1280.0f , i.goomba_origin_pos[j].y }), i.goomba_data[j].getOrigin());
			pos = { -1,-1 };
			for (unsigned int k = 0; k < i.data.size(); ++k) {
				const sf::FloatRect blockGlobal = getGlobalHitbox(block, i.data[k]);
				if (isCollide(goombaGlobal, blockGlobal)) {
					pos = { i.data[k].getPosition().x, i.data[k].getPosition().y };
					break;
				}
			}

			if (pos.y != -1) {
				i.goomba_origin_pos[j] = { i.goomba_origin_pos[j].x, pos.y - 31.0f };
				i.goomba_data[j].setGoombaYvelocity(0.0f);
			}
		}
	}
}

void GoombaHorizonUpdate(float dt) {
	sf::FloatRect block({ 0, 0 }, { 32, 32 });
	sf::Vector2f pos({ -1, -1 });
	for (auto& i : lvldata) {
		for (unsigned int j = 0; j < i.goomba_data.size(); ++j) {
			pos = { -1,-1 };
			if (!i.goomba_data[j].getGoombaDirection()) {
				const sf::FloatRect goombaGlobal = getGlobalHitbox(goombaright, sf::Vector2f({ i.goomba_origin_pos[j].x + i.pos * 1280.0f , i.goomba_origin_pos[j].y}), i.goomba_data[j].getOrigin());
				for (unsigned int k = 0; k < i.data.size(); ++k) {
					const sf::FloatRect blockGlobal = getGlobalHitbox(block, i.data[k]);
					if (isCollide(goombaGlobal, blockGlobal)) {
						pos = { i.data[k].getPosition().x, i.data[k].getPosition().y };
						break;
					}
				}
				if (pos.x != -1) {
					i.goomba_origin_pos[j] = { pos.x - 31.0f - i.pos * 1280.0f , i.goomba_origin_pos[j].y };
					i.goomba_data[j].setGoombaDirection(true);
				}
			}
			else if (i.goomba_data[j].getGoombaDirection()) {
				const sf::FloatRect goombaGlobal = getGlobalHitbox(goombaleft, sf::Vector2f({ i.goomba_origin_pos[j].x + i.pos * 1280.0f , i.goomba_origin_pos[j].y }), i.goomba_data[j].getOrigin());
				for (unsigned int k = 0; k < i.data.size(); ++k) {
					const sf::FloatRect blockGlobal = getGlobalHitbox(block, i.data[k]);
					if (isCollide(goombaGlobal, blockGlobal)) {
						pos = { i.data[k].getPosition().x, i.data[k].getPosition().y };
						break;
					}
				}
				if (pos.x != -1) {
					i.goomba_origin_pos[j] = { pos.x + 33.0f - i.pos * 1280.0f , i.goomba_origin_pos[j].y };
					i.goomba_data[j].setGoombaDirection(false);
				}
			}
		}
	}
}

//Draw Enemy
void DrawEnemy() {
	for (auto& i : lvldata) {
		for (auto& j : i.piranha_ground_data) {
			PiranhaGroundAnimation.update(j);
			rTexture.draw(j);
		}
		for (auto& j : i.goomba_data) {
			GoombaAnimation.silentupdate();
			j.setTextureRect(GoombaAnimation.getAnimationTextureRect(), true);
			rTexture.draw(j);
		}
	}
}