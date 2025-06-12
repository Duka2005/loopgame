#include <SFML/Graphics.hpp>
#include "../../Headers/Scenes/Mainmenu.hpp"
#include "../../Headers/Window.hpp"
#include "../../Headers/Sound.hpp"
#include <iostream>

float started = 0;
bool BlackBackgroundTrigger = false;

float mouse_x, mouse_y;

sf::Cursor cursorhand = sf::Cursor::createFromSystem(sf::Cursor::Type::Hand).value();
sf::Cursor cursorarrow = sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow).value();

sf::Texture backgroundmainmenutexture("Resources/Image/Mainmenu/backgroundmainmenu.png");
sf::Sprite backgroundmainmenu(backgroundmainmenutexture);
sf::Texture mariorunnertexture("Resources/Image/Mainmenu/MarioRunner.png");
sf::Sprite mariorunner(mariorunnertexture);
sf::Texture boxtexture("Resources/Image/Mainmenu/box.png");
sf::Sprite boxmainmenu(boxtexture);
sf::Texture starttexture("Resources/Image/Mainmenu/start.png");
sf::Sprite startbutton(starttexture);
sf::Texture optionstexture("Resources/Image/Mainmenu/options.png");
sf::Sprite optionsbutton(optionstexture);
sf::Texture quittexture("Resources/Image/Mainmenu/quit.png");
sf::Sprite quitbutton(quittexture);

sf::VertexArray blackscreen1(sf::PrimitiveType::TriangleStrip, 4);

void UpdateMousePosition() {
	const sf::Vector2i mouse = sf::Mouse::getPosition(window);
	mouse_x = (static_cast<float>(mouse.x) - ViewXOff / 2.0f) * (640.0f / (static_cast<float>(window.getSize().x) - ViewXOff));
	mouse_y = (static_cast<float>(mouse.y) - ViewYOff / 2.0f) * (480.0f / (static_cast<float>(window.getSize().y) - ViewYOff));
}

void SetMainmenuPos() {
	backgroundmainmenu.setPosition({ 0.0f, 0.0f });
	mariorunner.setPosition({ 120.0f, 0.0f });
	boxmainmenu.setPosition({ 177.0f,288.0f });
	startbutton.setPosition({ 279.0f,324.0f });
	optionsbutton.setPosition({ 268.0f,369.0f });
	quitbutton.setPosition({ 290.0f,415.0f });
	blackscreen1[0].color = blackscreen1[1].color = blackscreen1[2].color = blackscreen1[3].color = sf::Color(0, 0, 0, 0);
}

void BlackScreenProcess(bool& process, const float dt, float& started, sf::VertexArray& blackscreen1) {
	if (process) {
		if (started <= 255) {
			blackscreen1[0].color = blackscreen1[1].color = blackscreen1[2].color = blackscreen1[3].color = sf::Color(0, 0, 0, started);
			started += 2.0f * dt;
		}
	}
}

void ActiveButtonMainMenu() {
	float startbutton_x1 = startbutton.getPosition().x;
	float startbutton_x2 = startbutton_x1 + 82.0f;
	float startbutton_y1 = startbutton.getPosition().y;
	float startbutton_y2 = startbutton_y1 + 35.0f;

	float optionsbutton_x1 = optionsbutton.getPosition().x;
	float optionsbutton_x2 = optionsbutton_x1 + 104.0f;
	float optionsbutton_y1 = optionsbutton.getPosition().y;
	float optionsbutton_y2 = optionsbutton_y1 + 36.0f;

	float quitbutton_x1 = quitbutton.getPosition().x;
	float quitbutton_x2 = quitbutton_x1 + 60.0f;
	float quitbutton_y1 = quitbutton.getPosition().y;
	float quitbutton_y2 = quitbutton_y1 + 33.0f;

	blackscreen1[0].position = sf::Vector2f(-320.f + initx, 0.f);
	blackscreen1[1].position = sf::Vector2f(320.f + initx, 0.f);
	blackscreen1[2].position = sf::Vector2f(-320.f + initx, 480.f);
	blackscreen1[3].position = sf::Vector2f(320.f + initx, 480.f);

	if ((mouse_x >= startbutton_x1) && (mouse_x <= startbutton_x2) && (mouse_y >= startbutton_y1) && (mouse_y <= startbutton_y2) && !BlackBackgroundTrigger) {
		window.setMouseCursor(cursorhand);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			BlackBackgroundTrigger = true;
			window.setMouseCursor(cursorarrow);
		}
	}
	else if ((mouse_x < startbutton_x1) || (mouse_x > startbutton_x2) || (mouse_y < startbutton_y1) || (mouse_y > startbutton_y2)) {
		if (!((mouse_x >= optionsbutton_x1) && (mouse_x <= optionsbutton_x2) && (mouse_y >= optionsbutton_y1) && (mouse_y <= optionsbutton_y2))) {
			if (!((mouse_x >= quitbutton_x1) && (mouse_x <= quitbutton_x2) && (mouse_y >= quitbutton_y1) && (mouse_y <= quitbutton_y2))) {
				window.setMouseCursor(cursorarrow);
			}
		}
	}

	if ((mouse_x >= optionsbutton_x1) && (mouse_x <= optionsbutton_x2) && (mouse_y >= optionsbutton_y1) && (mouse_y <= optionsbutton_y2) && !BlackBackgroundTrigger) {
		window.setMouseCursor(cursorhand);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			CurrentScene = 1;
			window.setMouseCursor(cursorarrow);
		}
	}
	else if ((mouse_x < optionsbutton_x1) || (mouse_x > optionsbutton_x2) || (mouse_y < optionsbutton_y1) || (mouse_y > optionsbutton_y2)) {
		if (!((mouse_x >= startbutton_x1) && (mouse_x <= startbutton_x2) && (mouse_y >= startbutton_y1) && (mouse_y <= startbutton_y2))) {
			if (!((mouse_x >= quitbutton_x1) && (mouse_x <= quitbutton_x2) && (mouse_y >= quitbutton_y1) && (mouse_y <= quitbutton_y2))) {
				window.setMouseCursor(cursorarrow);
			}
		}
	}

	if ((mouse_x >= quitbutton_x1) && (mouse_x <= quitbutton_x2) && (mouse_y >= quitbutton_y1) && (mouse_y <= quitbutton_y2) && !BlackBackgroundTrigger) {
		window.setMouseCursor(cursorhand);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			mainmenumusic.stop();
			window.close();
		}
	}
	else if ((mouse_x < quitbutton_x1) || (mouse_x > quitbutton_x2) || (mouse_y < quitbutton_y1) || (mouse_y > quitbutton_y2)) {
		if (!((mouse_x >= startbutton_x1) && (mouse_x <= startbutton_x2) && (mouse_y >= startbutton_y1) && (mouse_y <= startbutton_y2))) {
			if (!((mouse_x >= optionsbutton_x1) && (mouse_x <= optionsbutton_x2) && (mouse_y >= optionsbutton_y1) && (mouse_y <= optionsbutton_y2))) {
				window.setMouseCursor(cursorarrow);
			}
		}
	}
}

void DrawMainMenu() {
	rTexture.draw(backgroundmainmenu);
	rTexture.draw(mariorunner);
	rTexture.draw(boxmainmenu);
	rTexture.draw(startbutton);
	rTexture.draw(optionsbutton);
	rTexture.draw(quitbutton);
	rTexture.draw(blackscreen1);
}