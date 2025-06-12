#include <SFML/Graphics.hpp>
#include "../../Headers/Scenes/Options.hpp"
#include "../../Headers/Scenes/Mainmenu.hpp"
#include "../../Headers/Window.hpp"
#include "../../Headers/Sound.hpp"

int musicvolume = 100;
int soundvolume = 100;

bool musicleftcanpress = false;
bool musicrightcanpress = false;
bool soundleftcanpress = false;
bool soundrightcanpress = false;
bool exitoptionscanpress = false;

sf::Texture optionsbgtexture("Resources/Image/Options/options_bg.png");
sf::Sprite  optionsbg(optionsbgtexture);
sf::Texture musicoptionstexture("Resources/Image/Options/music_options.png");
sf::Sprite  musicoptions(musicoptionstexture);
sf::Texture musiclefttexture("Resources/Image/Options/button_left.png");
sf::Sprite  musicleft(musiclefttexture);
sf::Texture musicrighttexture("Resources/Image/Options/button_right.png");
sf::Sprite  musicright(musicrighttexture);
sf::Texture soundoptionstexture("Resources/Image/Options/sound_options.png");
sf::Sprite  soundoptions(soundoptionstexture);
sf::Texture soundlefttexture("Resources/Image/Options/button_left.png");
sf::Sprite  soundleft(soundlefttexture);
sf::Texture soundrighttexture("Resources/Image/Options/button_right.png");
sf::Sprite  soundright(soundrighttexture);
sf::Texture exitoptionstexture("Resources/Image/Options/exit_options.png");
sf::Sprite  exitoptions(exitoptionstexture);


void SetOptionsPos() {
	optionsbg.setPosition({ 0.0f, 0.0f });
	musicoptions.setPosition({ 96.0f, 128.0f });
	musicleft.setPosition({ 128.0f + 92.0f, 136.0f });
	musicright.setPosition({ 128.0f + 92.0f + 64.0f + 10.0f, 136.0f });
	soundoptions.setPosition({ 96.0f, 174.0f });
	soundleft.setPosition({ 128.0f + 92.0f, 182.0f });
	soundright.setPosition({ 128.0f + 92.0f + 64.0f + 10.0f, 182.0f });
	exitoptions.setPosition({ 288.0f, 250.0f });
}

void ActiveButtonOptions() {
	const sf::Vector2i mouse = sf::Mouse::getPosition(window);
	mouse_x = (static_cast<float>(mouse.x) - ViewXOff / 2.0f) * (640 / (static_cast<float>(window.getSize().x) - ViewXOff));
	mouse_y = (static_cast<float>(mouse.y) - ViewYOff / 2.0f) * (480 / (static_cast<float>(window.getSize().y) - ViewYOff));

	float musicleft_x1 = musicleft.getPosition().x;
	float musicleft_x2 = musicleft_x1 + 16.0f;
	float musicleft_y1 = musicleft.getPosition().y;
	float musicleft_y2 = musicleft_y1 + 16.0f;

	float musicright_x1 = musicright.getPosition().x;
	float musicright_x2 = musicright_x1 + 16.0f;
	float musicright_y1 = musicright.getPosition().y;
	float musicright_y2 = musicright_y1 + 16.0f;

	float soundleft_x1 = soundleft.getPosition().x;
	float soundleft_x2 = soundleft_x1 + 16.0f;
	float soundleft_y1 = soundleft.getPosition().y;
	float soundleft_y2 = soundleft_y1 + 16.0f;

	float soundright_x1 = soundright.getPosition().x;
	float soundright_x2 = soundright_x1 + 16.0f;
	float soundright_y1 = soundright.getPosition().y;
	float soundright_y2 = soundright_y1 + 16.0f;

	float exitoptions_x1 = exitoptions.getPosition().x;
	float exitoptions_x2 = exitoptions_x1 + 64.0f;
	float exitoptions_y1 = exitoptions.getPosition().y;
	float exitoptions_y2 = exitoptions_y1 + 35.0f;

	if ((mouse_x >= musicleft_x1) && (mouse_x <= musicleft_x2) && (mouse_y >= musicleft_y1) && (mouse_y <= musicleft_y2) && !BlackBackgroundTrigger) {
		window.setMouseCursor(cursorhand);
		musicleftcanpress = true;
	}
	else if ((mouse_x < musicleft_x1) || (mouse_x > musicleft_x2) || (mouse_y < musicleft_y1) || (mouse_y > musicleft_y2)) {
		if (!((mouse_x >= musicright_x1) && (mouse_x <= musicright_x2) && (mouse_y >= musicright_y1) && (mouse_y <= musicright_y2))) {
			if (!((mouse_x >= soundleft_x1) && (mouse_x <= soundleft_x2) && (mouse_y >= soundleft_y1) && (mouse_y <= soundleft_y2))) {
				if (!((mouse_x >= soundright_x1) && (mouse_x <= soundright_x2) && (mouse_y >= soundright_y1) && (mouse_y <= soundright_y2))) {
					if (!((mouse_x >= exitoptions_x1) && (mouse_x <= exitoptions_x2) && (mouse_y >= exitoptions_y1) && (mouse_y <= exitoptions_y2))) {
						window.setMouseCursor(cursorarrow);
						musicleftcanpress = false;
					}
				}
			}
		}
	}

	if ((mouse_x >= musicright_x1) && (mouse_x <= musicright_x2) && (mouse_y >= musicright_y1) && (mouse_y <= musicright_y2) && !BlackBackgroundTrigger) {
		window.setMouseCursor(cursorhand);
		musicrightcanpress = true;
	}
	else if ((mouse_x < musicright_x1) || (mouse_x > musicright_x2) || (mouse_y < musicright_y1) || (mouse_y > musicright_y2)) {
		if (!((mouse_x >= musicleft_x1) && (mouse_x <= musicleft_x2) && (mouse_y >= musicleft_y1) && (mouse_y <= musicleft_y2))) {
			if (!((mouse_x >= soundleft_x1) && (mouse_x <= soundleft_x2) && (mouse_y >= soundleft_y1) && (mouse_y <= soundleft_y2))) {
				if (!((mouse_x >= soundright_x1) && (mouse_x <= soundright_x2) && (mouse_y >= soundright_y1) && (mouse_y <= soundright_y2))) {
					if (!((mouse_x >= exitoptions_x1) && (mouse_x <= exitoptions_x2) && (mouse_y >= exitoptions_y1) && (mouse_y <= exitoptions_y2))) {
						window.setMouseCursor(cursorarrow);
						musicrightcanpress = false;
					}
				}
			}
		}
	}

	if ((mouse_x >= soundleft_x1) && (mouse_x <= soundleft_x2) && (mouse_y >= soundleft_y1) && (mouse_y <= soundleft_y2) && !BlackBackgroundTrigger) {
		window.setMouseCursor(cursorhand);
		soundleftcanpress = true;
	}
	else if ((mouse_x < soundleft_x1) || (mouse_x > soundleft_x2) || (mouse_y < soundleft_y1) || (mouse_y > soundleft_y2)) {
		if (!((mouse_x >= musicleft_x1) && (mouse_x <= musicleft_x2) && (mouse_y >= musicleft_y1) && (mouse_y <= musicleft_y2))) {
			if (!((mouse_x >= musicright_x1) && (mouse_x <= musicright_x2) && (mouse_y >= musicright_y1) && (mouse_y <= musicright_y2))) {
				if (!((mouse_x >= soundright_x1) && (mouse_x <= soundright_x2) && (mouse_y >= soundright_y1) && (mouse_y <= soundright_y2))) {
					if (!((mouse_x >= exitoptions_x1) && (mouse_x <= exitoptions_x2) && (mouse_y >= exitoptions_y1) && (mouse_y <= exitoptions_y2))) {
						window.setMouseCursor(cursorarrow);
						soundleftcanpress = false;
					}
				}
			}
		}
	}

	if ((mouse_x >= soundright_x1) && (mouse_x <= soundright_x2) && (mouse_y >= soundright_y1) && (mouse_y <= soundright_y2) && !BlackBackgroundTrigger) {
		window.setMouseCursor(cursorhand);
		soundrightcanpress = true;
	}
	else if ((mouse_x < soundright_x1) || (mouse_x > soundright_x2) || (mouse_y < soundright_y1) || (mouse_y > soundright_y2)) {
		if (!((mouse_x >= musicleft_x1) && (mouse_x <= musicleft_x2) && (mouse_y >= musicleft_y1) && (mouse_y <= musicleft_y2))) {
			if (!((mouse_x >= musicright_x1) && (mouse_x <= musicright_x2) && (mouse_y >= musicright_y1) && (mouse_y <= musicright_y2))) {
				if (!((mouse_x >= soundleft_x1) && (mouse_x <= soundleft_x2) && (mouse_y >= soundleft_y1) && (mouse_y <= soundleft_y2))) {
					if (!((mouse_x >= exitoptions_x1) && (mouse_x <= exitoptions_x2) && (mouse_y >= exitoptions_y1) && (mouse_y <= exitoptions_y2))) {
						window.setMouseCursor(cursorarrow);
						soundrightcanpress = false;
					}
				}
			}
		}
	}

	if ((mouse_x >= exitoptions_x1) && (mouse_x <= exitoptions_x2) && (mouse_y >= exitoptions_y1) && (mouse_y <= exitoptions_y2) && !BlackBackgroundTrigger) {
		window.setMouseCursor(cursorhand);
		exitoptionscanpress = true;
	}
	else if ((mouse_x < exitoptions_x1) || (mouse_x > exitoptions_x2) || (mouse_y < exitoptions_y1) || (mouse_y > exitoptions_y2)) {
		if (!((mouse_x >= musicleft_x1) && (mouse_x <= musicleft_x2) && (mouse_y >= musicleft_y1) && (mouse_y <= musicleft_y2))) {
			if (!((mouse_x >= musicright_x1) && (mouse_x <= musicright_x2) && (mouse_y >= musicright_y1) && (mouse_y <= musicright_y2))) {
				if (!((mouse_x >= soundleft_x1) && (mouse_x <= soundleft_x2) && (mouse_y >= soundleft_y1) && (mouse_y <= soundleft_y2))) {
					if (!((mouse_x >= soundright_x1) && (mouse_x <= soundright_x2) && (mouse_y >= soundright_y1) && (mouse_y <= soundright_y2))) {
						window.setMouseCursor(cursorarrow);
						exitoptionscanpress = false;
					}
				}
			}
		}
	}
}

void DrawOptions() {
	rTexture.draw(optionsbg);
	rTexture.draw(musicoptions);
	rTexture.draw(musicleft);
	rTexture.draw(musicright);
	rTexture.draw(soundoptions);
	rTexture.draw(soundleft);
	rTexture.draw(soundright);
	rTexture.draw(exitoptions);
}