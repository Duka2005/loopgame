#include <SFML/Graphics.hpp>
#include <algorithm>

#include <iostream>
#include "../Headers/Window.hpp"
#include "../Headers/Mario.hpp"
#include "../Headers/Sound.hpp"

bool GAME_PAUSE = false;

sf::Clock Gameclock;

sf::RenderWindow window(sf::VideoMode({ 640, 480 }), "Mario Runner!");
sf::RenderTexture rTexture({ 640, 480 });
sf::View viewwin;
sf::View view;

int CurrentScene = 0;

int scoregame = 0;

float ViewXOff, ViewYOff;

float speedtime = 2.0f;
float prev_speedtime = speedtime;
float initx = 320.0f;
float prev_initx = 320.0f;

float stage1 = 120.0f;
float stage2 = 240.0f;
float stage3 = 480.0f;

sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight) {
	// Compares the aspect ratio of the window to the aspect ratio of the view,
	// and sets the view's viewport accordingly in order to achieve a letterbox effect.
	// A new view (with a new viewport set) is returned.

	float windowRatio = (float)windowWidth / (float)windowHeight;
	float viewRatio = view.getSize().x / (float)view.getSize().y;
	float sizeX = 1;
	float sizeY = 1;
	float posX = 0;
	float posY = 0;

	bool horizontalSpacing = true;
	if (windowRatio < viewRatio)
		horizontalSpacing = false;

	// If horizontalSpacing is true, the black bars will appear on the left and right side.
	// Otherwise, the black bars will appear on the top and bottom.

	if (horizontalSpacing) {
		sizeX = viewRatio / windowRatio;
		posX = (1 - sizeX) / 2.f;
	}

	else {
		sizeY = windowRatio / viewRatio;
		posY = (1 - sizeY) / 2.f;
	}

	view.setViewport(sf::FloatRect({ posX, posY }, { sizeX, sizeY }));

	return view;
}
void ViewInit() {
	view = sf::View(sf::FloatRect({ 0, 0 }, { 640, 480 }));
}
void updateView() {
	const float vx = window.getSize().x / 640.0f;
	const float vy = window.getSize().y / 480.0f;
	const float min = std::min(vx, vy);
	ViewXOff = window.getSize().x - (640.0f * min);
	ViewYOff = window.getSize().y - (480.0f * min);
	viewwin = getLetterboxView(view, window.getSize().x, window.getSize().y);
	view.setCenter({ std::round(initx), 240.0f});
	viewwin.setCenter(sf::Vector2f({ 640.0f / 2.0f, 480.0f / 2.0f }));
}
void setView(float dt) {
	if (processdeath) {
		speedtime -= (speedtime > 0.0f ? 0.1f * dt : 0.0f);
		if (speedtime <= 0.0f) speedtime = 0.0f;
	}
	initx += dt * speedtime;
}

bool isOutScreenRight(const sf::Vector2f& pos, const sf::Vector2f& offset) {
	if (initx + 320.0f + offset.x > pos.x) return false;
	else return true;
}

void checktimeupspeed() {
	if (!processdeath) {
		if (prev_speedtime == 2.0f && Gameclock.getElapsedTime().asSeconds() >= stage1 && Gameclock.getElapsedTime().asSeconds() < stage2) {
			speedup.play();
			speedtime = 2.5f;
			prev_speedtime = speedtime;
		}
		else if (prev_speedtime == 2.5f && Gameclock.getElapsedTime().asSeconds() >= stage2 && Gameclock.getElapsedTime().asSeconds() < stage3) {
			speedup.play();
			speedtime = 3.0f;
			prev_speedtime = speedtime;
		}
		else if (prev_speedtime == 3.0f && Gameclock.getElapsedTime().asSeconds() >= stage3) {
			speedup.play();
			speedtime = 3.5f;
			prev_speedtime = speedtime;
		}
	}
}