#include <SFML/Graphics.hpp>
#include "../Headers/GameClass.hpp"
#include "../Headers/Enemy.hpp"
#include "../Headers/LocalAnimationManager.hpp"
#include "../Headers/Mario.hpp"
#include "../Headers/Level.hpp"
#include "../Headers/Window.hpp"
#include <vector>

sf::Texture PiranhaGroundTexture("Resources/Image/Enemy/PiranhaGround.png");
sf::Texture GoombaTexture("Resources/Image/Enemy/Goomba.png");

LocalAnimationManager PiranhaGroundAnimation;
LocalAnimationManager GoombaAnimation;

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
			i.goomba_data[j].setGoombaXvelocity(i.goomba_data[j].getGoombaXvelocity() + (i.goomba_data[j].getGoombaXvelocity() > i.goomba_data[j].getGoombaSpeed() ? 0.0f : 0.125f * dt));

			if (i.goomba_data[j].getGoombaDirection()) i.goomba_origin_pos[j] = { i.goomba_origin_pos[j].x - i.goomba_data[j].getGoombaXvelocity() * dt, i.goomba_origin_pos[j].y };
			if (!i.goomba_data[j].getGoombaDirection()) i.goomba_origin_pos[j] = { i.goomba_origin_pos[j].x + i.goomba_data[j].getGoombaXvelocity() * dt, i.goomba_origin_pos[j].y };
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