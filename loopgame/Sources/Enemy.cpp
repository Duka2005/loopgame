#include <SFML/Graphics.hpp>
#include "../Headers/GameClass.hpp"
#include "../Headers/Enemy.hpp"
#include "../Headers/LocalAnimationManager.hpp"
#include "../Headers/Mario.hpp"
#include "../Headers/Level.hpp"
#include "../Headers/Window.hpp"
#include "../Headers/Sound.hpp"
#include "../Headers/EnemyDeath.hpp"
#include <vector>
#include <iostream>
sf::Texture PiranhaGroundTexture("Resources/Image/Enemy/PiranhaGround.png");
sf::Texture GoombaTexture("Resources/Image/Enemy/Goomba.png");
sf::Texture SpinyTexture("Resources/Image/Enemy/RedSpiny.png");

LocalAnimationManager PiranhaGroundAnimation;
LocalAnimationManager GoombaAnimation;
LocalAnimationManager SpinyAnimation;

sf::FloatRect goombafoot({ 1 ,32 }, { 30,2 });
sf::FloatRect goombaleft({ -1,4 }, { 2,27 });
sf::FloatRect goombaright({ 30,4 }, { 2,27 });

sf::FloatRect spinyfoot({ 1 ,32 }, { 30,2 });
sf::FloatRect spinyleft({ -1,4 }, { 2,27 });
sf::FloatRect spinyright({ 30,4 }, { 2,27 });

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
	for (auto& i : lvldata) {
		for (unsigned j = 0; j < i.goomba_data.size(); ++j) {
			if (isCollide(mariomain, mario, getGlobalHitbox(GoombaHitBox, i.goomba_data[j].getPosition(), i.goomba_data[j].getOrigin()))) {
				if (((i.goomba_data[j].getPosition().y - 16.0f) <= mario.getPosition().y) && (Yvelocity > 0.0f)) {
					if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) Yvelocity = -9.0f;
					else Yvelocity = -14.0f;
					goombadeath.play();
					AddGoombaDeath(i.goomba_origin_pos[j].x + 1280 * i.pos, i.goomba_origin_pos[j].y);
					DeleteGoomba(i.goomba_origin_pos[j].x, i.goomba_origin_pos[j].y);
					break;
				}
				else{
					MarioDeath();
					break;
				}
			}
		}
	}
}

void DeleteGoomba(const float x, const float y) {
	bool flag = false;
	for (auto& i : lvldata) {
		for (unsigned j = 0; j < i.goomba_data.size(); ++j) {
			if (i.goomba_origin_pos[j].x == x && i.goomba_origin_pos[j].y == y) {
				i.goomba_data.erase(i.goomba_data.begin() + j);
				i.goomba_origin_pos.erase(i.goomba_origin_pos.begin() + j);
				flag = true;
				break;
			}
		}
		if (flag) break;
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
//Spiny
float SpinyXvelocity = 0.0f;
float SpinyYvelocity = 0.0f;
float SpinySpeed;
bool FirstSpinyDirection = true;
bool SpinyDirection = FirstSpinyDirection;

void AddSpiny(Level& lvl, float x, float y) {
	lvl.spiny_data.push_back(SpinyEnemy(SpinyTexture));
	lvl.spiny_origin_pos.push_back(sf::Vector2f({ x,y }));
	lvl.spiny_data.back().m_animation.setAnimation(0, 1, 33, 32, 0, 14);
}

void CheckSpinyCollision() {
	sf::FloatRect SpinyHitBox({ 0, 0 }, { 33, 32 });
	if (processdeath) return;
	for (const auto& i : lvldata) {
		for (const auto& j : i.spiny_data) {
			if (isCollide(mariomain, mario, getGlobalHitbox(SpinyHitBox, j.getPosition(), j.getOrigin()))) {
				MarioDeath();
				break;
			}
		}
	}
}

void SpinyMovement(float dt) {
	for (auto& i : lvldata) {
		for (unsigned int j = 0; j < i.spiny_data.size(); ++j) {
			if (i.spiny_data[j].getSpinyXvelocity() < 1.0f && i.spiny_data[j].getSpinyDirection()) i.spiny_data[j].setSpinyXvelocity(1.0f);

			if (i.spiny_data[j].getSpinyDirection()) i.spiny_origin_pos[j] = { i.spiny_origin_pos[j].x - i.spiny_data[j].getSpinyXvelocity() * dt, i.spiny_origin_pos[j].y };
			if (!i.spiny_data[j].getSpinyDirection()) i.spiny_origin_pos[j] = { i.spiny_origin_pos[j].x + i.spiny_data[j].getSpinyXvelocity() * dt, i.spiny_origin_pos[j].y };
		}

	}
}

void SpinyVerticleUpdate(float dt) {
	sf::FloatRect block({ 0, 0 }, { 32, 32 });
	sf::Vector2f pos({ -1, -1 });
	for (auto& i : lvldata) {
		for (unsigned int j = 0; j < i.spiny_data.size(); ++j) {
			i.spiny_data[j].setSpinyYvelocity(i.spiny_data[j].getSpinyYvelocity() + (i.spiny_data[j].getSpinyYvelocity() < 10.0f ? 1.0f * dt * 0.3f : 0.0f));
			if (i.spiny_data[j].getSpinyYvelocity() > 10.0f) i.spiny_data[j].setSpinyYvelocity(10.0f);
			i.spiny_origin_pos[j] = { i.spiny_origin_pos[j].x, i.spiny_origin_pos[j].y + i.spiny_data[j].getSpinyYvelocity() * dt };

			const sf::FloatRect spinyGlobal = getGlobalHitbox(spinyfoot, sf::Vector2f({ i.spiny_origin_pos[j].x + i.pos * 1280.0f , i.spiny_origin_pos[j].y }), i.spiny_data[j].getOrigin());
			pos = { -1,-1 };
			for (unsigned int k = 0; k < i.data.size(); ++k) {
				const sf::FloatRect blockGlobal = getGlobalHitbox(block, i.data[k]);
				if (isCollide(spinyGlobal, blockGlobal)) {
					pos = { i.data[k].getPosition().x, i.data[k].getPosition().y };
					break;
				}
			}

			if (pos.y != -1) {
				i.spiny_origin_pos[j] = { i.spiny_origin_pos[j].x, pos.y - 31.0f };
				i.spiny_data[j].setSpinyYvelocity(0.0f);
			}
		}
	}
}

void SpinyHorizonUpdate(float dt) {
	sf::FloatRect block({ 0, 0 }, { 32, 32 });
	sf::Vector2f pos({ -1, -1 });
	for (auto& i : lvldata) {
		for (unsigned int j = 0; j < i.spiny_data.size(); ++j) {
			pos = { -1,-1 };
			if (!i.spiny_data[j].getSpinyDirection()) {
				const sf::FloatRect spinyGlobal = getGlobalHitbox(spinyright, sf::Vector2f({ i.spiny_origin_pos[j].x + i.pos * 1280.0f , i.spiny_origin_pos[j].y }), i.spiny_data[j].getOrigin());
				for (unsigned int k = 0; k < i.data.size(); ++k) {
					const sf::FloatRect blockGlobal = getGlobalHitbox(block, i.data[k]);
					if (isCollide(spinyGlobal, blockGlobal)) {
						pos = { i.data[k].getPosition().x, i.data[k].getPosition().y };
						break;
					}
				}
				if (pos.x != -1) {
					i.spiny_origin_pos[j] = { pos.x - 31.0f - i.pos * 1280.0f , i.spiny_origin_pos[j].y };
					i.spiny_data[j].setSpinyDirection(true);
					i.spiny_data[j].m_animation.setYPos(1);
				}
			}
			else if (i.spiny_data[j].getSpinyDirection()) {
				const sf::FloatRect spinyGlobal = getGlobalHitbox(spinyleft, sf::Vector2f({ i.spiny_origin_pos[j].x + i.pos * 1280.0f , i.spiny_origin_pos[j].y }), i.spiny_data[j].getOrigin());
				for (unsigned int k = 0; k < i.data.size(); ++k) {
					const sf::FloatRect blockGlobal = getGlobalHitbox(block, i.data[k]);
					if (isCollide(spinyGlobal, blockGlobal)) {
						pos = { i.data[k].getPosition().x, i.data[k].getPosition().y };
						break;
					}
				}
				if (pos.x != -1) {
					i.spiny_origin_pos[j] = { pos.x + 33.0f - i.pos * 1280.0f , i.spiny_origin_pos[j].y };
					i.spiny_data[j].setSpinyDirection(false);
					i.spiny_data[j].m_animation.setYPos(0);
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
		for (auto& j : i.spiny_data) {
			j.m_animation.silentupdate();
			j.setTextureRect(j.m_animation.getAnimationTextureRect(), true);
			rTexture.draw(j);
		}
	}
}