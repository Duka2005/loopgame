#include <SFML/Graphics.hpp>
#include "../Headers/Enemy.hpp"
#include "../Headers/LocalAnimationManager.hpp"
#include "../Headers/Mario.hpp"
#include "../Headers/Level.hpp"
#include "../Headers/Window.hpp"
#include <vector>

sf::Texture PiranhaGroundTexture("Resources/Image/Enemy/PiranhaGround.png");

LocalAnimationManager PiranhaGroundAnimation;

void AddPiranhaGround(Level& lvl, float x, float y) {
	lvl.piranha_ground_data.push_back(sf::Sprite(PiranhaGroundTexture));
	lvl.piranha_ground_origin_pos.push_back(sf::Vector2f({ x ,y }));
}

void PiranhaGroundAnimationInit() {
	PiranhaGroundAnimation.setAnimation(0, 3, 32, 32, 0, 22);
}

void DrawPiranhaGround() {
	for (auto& i : lvldata) {
		for (auto& j : i.piranha_ground_data) {
			PiranhaGroundAnimation.update(j);
			rTexture.draw(j);
		}
	}
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