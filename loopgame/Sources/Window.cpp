#include <SFML/Graphics.hpp>
#include <algorithm>

#include <iostream>
#include "../Headers/Window.hpp"
#include "../Headers/Mario.hpp"

sf::RenderWindow window(sf::VideoMode({ 640, 480 }), "Mario Runner!");
sf::RenderTexture rTexture({ 640, 480 });
sf::View viewwin;
sf::View view;

float speedtime = 2.0f;
float initx = 320.0f;

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
	viewwin = getLetterboxView(view, window.getSize().x, window.getSize().y);
	view.setCenter({ initx, 240.0f});
	viewwin.setCenter(sf::Vector2f({ 640 / 2, 480 / 2 }));
}
void setView(float dt) {
	initx += dt * speedtime;
	//std::cout << initx << "\n";
}