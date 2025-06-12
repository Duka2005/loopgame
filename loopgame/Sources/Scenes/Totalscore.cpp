#include <SFML/Graphics.hpp>
#include "../../Headers/Scenes/Totalscore.hpp"
#include "../../Headers/Scenes/Mainmenu.hpp"
#include "../../Headers/Window.hpp"
#include "../../Headers/Sound.hpp"

sf::Texture totalscorebgtexture("Resources/Image/TotalScore/totalscore_bg.png");
sf::Sprite  totalscorebg(totalscorebgtexture);
sf::Texture mainmenutotalscoretexture("Resources/Image/TotalScore/mainmenu_totalscore.png");
sf::Sprite  mainmenutotalscore(mainmenutotalscoretexture);
sf::Texture playagaintexture("Resources/Image/TotalScore/playagain.png");
sf::Sprite  playagain(playagaintexture);
sf::Texture gameovertexture("Resources/Image/TotalScore/thegameover.png");
sf::Sprite  gameover(gameovertexture);

void SetTotalScorePos() {
	totalscorebg.setPosition({ 0.0f, 0.0f });
	mainmenutotalscore.setPosition({ 330.0f, 250.0f });
	playagain.setPosition({ 122.0f, 250.0f });
	gameover.setPosition({ 64.0f, 32.0f });
}

void ActiveTotalScore() {
	float mainmenutotalscore_x1 = mainmenutotalscore.getPosition().x;
	float mainmenutotalscore_x2 = mainmenutotalscore_x1 + 176.0f;
	float mainmenutotalscore_y1 = mainmenutotalscore.getPosition().y;
	float mainmenutotalscore_y2 = mainmenutotalscore_y1 + 34.0f;

	float playagain_x1 = playagain.getPosition().x;
	float playagain_x2 = playagain_x1 + 188.0f;
	float playagain_y1 = playagain.getPosition().y;
	float playagain_y2 = playagain_y1 + 34.0f;

	if ((mouse_x >= mainmenutotalscore_x1) && (mouse_x <= mainmenutotalscore_x2) && (mouse_y >= mainmenutotalscore_y1) && (mouse_y <= mainmenutotalscore_y2) && !BlackBackgroundTrigger) {
		window.setMouseCursor(cursorhand);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			totalscoremusic.stop();
			scoregame = 0;
			CurrentScene = 0;
		}
	}
	else if ((mouse_x < mainmenutotalscore_x1) || (mouse_x > mainmenutotalscore_x2) || (mouse_y < mainmenutotalscore_y1) || (mouse_y > mainmenutotalscore_y2)) {
		if (!((mouse_x >= playagain_x1) && (mouse_x <= playagain_x2) && (mouse_y >= playagain_y1) && (mouse_y <= playagain_y2))) {
			window.setMouseCursor(cursorarrow);
		}
	}

	if ((mouse_x >= playagain_x1) && (mouse_x <= playagain_x2) && (mouse_y >= playagain_y1) && (mouse_y <= playagain_y2) && !BlackBackgroundTrigger) {
		window.setMouseCursor(cursorhand);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			BlackBackgroundTrigger = true;
			window.setMouseCursor(cursorarrow);
		}
	}
	else if ((mouse_x < playagain_x1) || (mouse_x > playagain_x2) || (mouse_y < playagain_y1) || (mouse_y > playagain_y2)) {
		if (!((mouse_x >= mainmenutotalscore_x1) && (mouse_x <= mainmenutotalscore_x2) && (mouse_y >= mainmenutotalscore_y1) && (mouse_y <= mainmenutotalscore_y2))) {
			window.setMouseCursor(cursorarrow);
		}
	}
}

void TotalScoreDraw() {
	rTexture.draw(mainmenutotalscore);
	rTexture.draw(playagain);
	rTexture.draw(gameover);
}