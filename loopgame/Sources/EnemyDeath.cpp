#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "../Headers/EnemyDeath.hpp"
#include "../Headers/Enemy.hpp"
#include "../Headers/Mario.hpp"
#include "../Headers/Window.hpp"
#include <vector>

sf::Texture GoombaDeathTexture("Resources/Image/Death/goomba_death.png");

sf::FloatRect goombadeathfoot({ 1 ,32 }, { 30,2 });

std::vector<sf::Sprite> GoombaDeathList;
std::vector<float> GoombaDeathYVeloList;
std::vector<sf::Clock> GoombaDeathClockList;

void AddGoombaDeath(float x, float y) {
	GoombaDeathList.emplace_back(sf::Sprite(GoombaDeathTexture));
	GoombaDeathList.back().setPosition({ x,y });
	GoombaDeathYVeloList.emplace_back(0.0f);
	GoombaDeathClockList.emplace_back(sf::Clock());
	GoombaDeathClockList.back().restart();
}

void GoombaDeathVerticleUpdate(float dt) {
	sf::FloatRect block({ 0, 0 }, { 32, 32 });
	sf::Vector2f pos({ -1, -1 });
	bool flag = false;
	for (unsigned int i = 0; i < GoombaDeathList.size(); ++i) {
		GoombaDeathYVeloList[i] += (GoombaDeathYVeloList[i] < 10.0f ? 1.0f * dt * 0.3f : 0.0f);
		if (GoombaDeathYVeloList[i] > 10.0f) GoombaDeathYVeloList[i] = 10.0f;
		GoombaDeathList[i].move({0.f, GoombaDeathYVeloList[i] * dt});

		const sf::FloatRect goombaGlobal = getGlobalHitbox(goombadeathfoot, GoombaDeathList[i].getPosition(), {0,0});
		pos = { -1,-1 };
		flag = false;
		for (auto& j : lvldata) {
			for (unsigned int k = 0; k < j.data.size(); ++k) {
				const sf::FloatRect blockGlobal = getGlobalHitbox(block, j.data[k]);
				if (isCollide(goombaGlobal, blockGlobal)) {
					pos = { j.data[k].getPosition().x, j.data[k].getPosition().y };
					flag = true;
					break;
				}
			}
			if (flag) break;
		}

		if (pos.y != -1) {
			GoombaDeathList[i].setPosition({ GoombaDeathList[i].getPosition().x, pos.y - 31.0f });
			GoombaDeathYVeloList[i] = 0.0f;
		}
	}
}

void DrawGoombaDeath() {
	for (auto& i : GoombaDeathList) {
		rTexture.draw(i);
	}
}

void DeleteGoombaDeath(const float x, const float y) {
	for (unsigned i = 0; i < GoombaDeathList.size(); ++i) {
		if (GoombaDeathList[i].getPosition().x == x && GoombaDeathList[i].getPosition().y == y) {
			GoombaDeathList.erase(GoombaDeathList.begin() + i);
			GoombaDeathYVeloList.erase(GoombaDeathYVeloList.begin() + i);
			GoombaDeathClockList.erase(GoombaDeathClockList.begin() + i);
			break;
		}
	}
}

void GoombaDeathPause() {
	for (auto& i : GoombaDeathClockList) {
		if (i.isRunning()) i.stop();
		else i.start();
	}
}

void TimeVisibleGoombaDeath() {
	if (GAME_PAUSE) return;
	for (unsigned i = 0; i < GoombaDeathList.size(); ++i) {
		if (GoombaDeathClockList[i].getElapsedTime().asSeconds() >= 4) {
			DeleteGoombaDeath(GoombaDeathList[i].getPosition().x, GoombaDeathList[i].getPosition().y);
			break;
		}
	}
}