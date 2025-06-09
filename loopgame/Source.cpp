#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "Headers/Mario.hpp"
#include "Headers/Tileset.hpp"
#include "Headers/Window.hpp"
#include "Headers/Kairos.hpp"
#include "Headers/GenLevel.hpp"
#include "Headers/BackgroundColor.hpp"
#include "Headers/Sound.hpp"
#include "Headers/Enemy.hpp"
#include "Headers/EnemyDeath.hpp"
#include "Headers/Text.hpp"

#include <ctre.hpp>

int main()
{
	int CurrentScene = 0;

	float mouse_x, mouse_y;

	const auto cursorhand = sf::Cursor::createFromSystem(sf::Cursor::Type::Hand).value();
	const auto cursorarrow = sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow).value();

	//Icon
	sf::Image icon;
	icon.loadFromFile("icon.png");
	window.setIcon(icon);

	//Mainmenu
	sf::Texture backgroundmainmenutexture("Resources/Image/Mainmenu/backgroundmainmenu.png");
	sf::Sprite  backgroundmainmenu(backgroundmainmenutexture);
	backgroundmainmenu.setPosition({ initx - 320.0f, 0 });
	sf::Texture boxtexture("Resources/Image/Mainmenu/box.png");
	sf::Sprite  boxmainmenu(boxtexture);
	boxmainmenu.setPosition({ 177.0f,288.0f });
	sf::Texture starttexture("Resources/Image/Mainmenu/start.png");
	sf::Sprite  startbutton(starttexture);
	startbutton.setPosition({ 279.0f,324.0f });
	sf::Texture optionstexture("Resources/Image/Mainmenu/options.png");
	sf::Sprite  optionsbutton(optionstexture);
	optionsbutton.setPosition({ 268.0f,369.0f });
	sf::Texture quittexture("Resources/Image/Mainmenu/quit.png");
	sf::Sprite  quitbutton(quittexture);
	quitbutton.setPosition({ 290.0f,415.0f });

	//Gameplay
	int scoregame = 0;

	Gameclock.reset();

	sf::VertexArray blackscreen(sf::PrimitiveType::TriangleStrip, 4);
	blackscreen[0].color = blackscreen[1].color = blackscreen[2].color = blackscreen[3].color = sf::Color(0, 0, 0, 128);

	kairos::Timestep timestep;
	kairos::FpsLite fpsGame;
	timestep.setStep(1.0f / 500.0f);
	timestep.setMaxAccumulation(1.0f / 40.0f);

	music.setLooping(true);
	mainmenumusic.setLooping(true);

	BgColorInitColor();
	MarioInit();
	ViewInit();
	LevelInit();
	FontInit();
	SetMarioPosition(320, 416);

	PiranhaGroundAnimationInit();
	GoombaAnimationInit();

	bool GamePasueSound = false;

	float delta_initx = 0.0f;
	AddText("SCORE", "", 32, 40);
	AddText("SCORETEXT", "SCORE", 32, 24);
	AddText("FPS", "", 0, 464);
	AddText("PAUSETEXT1", "GAME PAUSED", 232, 416);
	AddText("PAUSETEXT2", "PRESS P TO CONTINUE", 168, 432);

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>())
				window.close();
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->scancode == sf::Keyboard::Scancode::P) {
					GAME_PAUSE = !GAME_PAUSE;
				}

			}
		}
		
		if (CurrentScene == 0) {
			if (!(mainmenumusic.getStatus() == sf::Music::Status::Playing)) mainmenumusic.play();
			const sf::Vector2i mouse = sf::Mouse::getPosition(window);
			mouse_x = (static_cast<float>(mouse.x) - ViewXOff / 2.0f) * (640 / (static_cast<float>(window.getSize().x) - ViewXOff));
			mouse_y = (static_cast<float>(mouse.y) - ViewYOff / 2.0f) * (480 / (static_cast<float>(window.getSize().y) - ViewYOff));


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

			if ((mouse_x >= startbutton_x1) && (mouse_x <= startbutton_x2) && (mouse_y >= startbutton_y1) && (mouse_y <= startbutton_y2)) {
				window.setMouseCursor(cursorhand);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
					mainmenumusic.stop();
					CurrentScene = 2;
				}
			}
			else if ((mouse_x < startbutton_x1) || (mouse_x > startbutton_x2) || (mouse_y < startbutton_y1) || (mouse_y > startbutton_y2)) {
				if (!((mouse_x >= optionsbutton_x1) && (mouse_x <= optionsbutton_x2) && (mouse_y >= optionsbutton_y1) && (mouse_y <= optionsbutton_y2))) {
					if (!((mouse_x >= quitbutton_x1) && (mouse_x <= quitbutton_x2) && (mouse_y >= quitbutton_y1) && (mouse_y <= quitbutton_y2))) {
						window.setMouseCursor(cursorarrow);
					}
				}
			}

			if ((mouse_x >= optionsbutton_x1) && (mouse_x <= optionsbutton_x2) && (mouse_y >= optionsbutton_y1) && (mouse_y <= optionsbutton_y2)) {
				window.setMouseCursor(cursorhand);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				}
			}
			else if ((mouse_x < optionsbutton_x1) || (mouse_x > optionsbutton_x2) || (mouse_y < optionsbutton_y1) || (mouse_y > optionsbutton_y2)) {
				if (!((mouse_x >= startbutton_x1) && (mouse_x <= startbutton_x2) && (mouse_y >= startbutton_y1) && (mouse_y <= startbutton_y2))) {
					if (!((mouse_x >= quitbutton_x1) && (mouse_x <= quitbutton_x2) && (mouse_y >= quitbutton_y1) && (mouse_y <= quitbutton_y2))) {
						window.setMouseCursor(cursorarrow);
					}
				}
			}

			if ((mouse_x >= quitbutton_x1) && (mouse_x <= quitbutton_x2) && (mouse_y >= quitbutton_y1) && (mouse_y <= quitbutton_y2)) {
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
			
			updateView();
			rTexture.setView(view);
			window.setView(viewwin);

			window.clear();
			rTexture.clear();
			rTexture.draw(backgroundmainmenu);
			rTexture.draw(boxmainmenu);
			rTexture.draw(startbutton);
			rTexture.draw(optionsbutton);
			rTexture.draw(quitbutton);
			rTexture.display();

			window.draw(sf::Sprite(rTexture.getTexture()));
			window.display();
		}


		else if (CurrentScene == 2) {
			//std::cout << (!Gameclock.isRunning() ? "FALSE" : "TRUE") << "\n";

			if (!Gameclock.isRunning()) Gameclock.start();
			if (!GAME_PAUSE) {
				if (!Gameclock.isRunning()) Gameclock.start();
				if (!MarioDeathClock.isRunning() && (processdeath || isactive)) {
					MarioDeathClock.start();
					death.play();
				}
				if (!(music.getStatus() == sf::Music::Status::Playing) && !processdeath && !isactive) {
					window.setMouseCursor(cursorarrow);
					music.play();
				}
				GoombaDeathPause();
			}
			else {
				if (Gameclock.isRunning()) Gameclock.stop();
				if (MarioDeathClock.isRunning() && (processdeath || isactive)) {
					MarioDeathClock.stop();
					death.pause();
				}
				if (music.getStatus() == sf::Music::Status::Playing && !processdeath && !isactive) music.pause();
				GoombaDeathPause();
			}

			if (mario.getPosition().y > 480 + 34 && !processdeath) {
				MarioDeath();
			}
			if (MarioDeathClock.getElapsedTime().asSeconds() >= 4) {
				death.stop();
				CurrentScene = 0;
				SetMarioPosition(320, 416);
				MarioDeathClock.reset();
				processdeath = false;
				CanMarioControl = true;
				initx = 320.0f;
				speedtime = 2.0f;
				scoregame = 0;
				prev_speedtime = 2.0f;
				DeleteAllLevel();
				LevelInit();
				MarioDirection = FirstMarioDirection;
				Gameclock.reset();
			}

			if(scoregame != 0) EditText(std::to_string(scoregame) + "00", "SCORE");
			else EditText(std::to_string(scoregame), "SCORE");
			EditText("FPS: " + std::to_string(static_cast<int>(fpsGame.getFps())), "FPS");

			//Check when to generate map
			timestep.pause();

			prev_initx = initx;
			fpsGame.update();
			timestep.addFrame();
			while (timestep.isUpdateRequired()) {
				const float dt = timestep.getStepAsFloat() * 50.0f;
				if (!GAME_PAUSE) {
					MarioMovement(dt);
					MarioHorizonUpdate(dt);
					MarioVerticleUpdate(dt);
					MoveFromOffset();
					MarioDeathUpdate(dt);
					GoombaHorizonUpdate(dt);
					GoombaVerticleUpdate(dt);
					GoombaMovement(dt);
					GoombaDeathVerticleUpdate(dt);
					SpinyHorizonUpdate(dt);
					SpinyVerticleUpdate(dt);
					PiranhaAIMovementUpdate(dt);
					SpinyMovement(dt);
					setView(dt);
				}
			}
			delta_initx += initx - prev_initx;
			if (static_cast<int>(delta_initx) - 160 >= 0) {
				delta_initx -= 160;
				scoregame += 1;
			}

			GoombaStatusUpdate();
			SpinyStatusUpdate();

			CheckLevelAvaliable();
			LevelUpdatePos();
			updateView();
			UpdatePositionCharacter();
			BgColorInitPos();

			blackscreen[0].position = sf::Vector2f(-320.f + initx, 0.f);
			blackscreen[1].position = sf::Vector2f(320.f + initx, 0.f);
			blackscreen[2].position = sf::Vector2f(-320.f + initx, 480.f);
			blackscreen[3].position = sf::Vector2f(320.f + initx, 480.f);

			CheckPiranhaGroundCollision();
			CheckPiranhaCollision();
			CheckGoombaCollision();
			CheckSpinyCollision();
			MarioStuck();
			TimeVisibleGoombaDeath();

			updateAnimation();

			checktimeupspeed();

			rTexture.clear();
			rTexture.setView(view);
			window.setView(viewwin);
			rTexture.draw(Backgroundcolor);
			DrawEnemy();
			LevelDraw();
			DrawGoombaDeath();
			if (CanMarioControl) rTexture.draw(mario);
			else rTexture.draw(mariodeath);
			if (GAME_PAUSE) {
				rTexture.draw(blackscreen);
				if (!GamePasueSound) {
					pausesound.play();
					GamePasueSound = true;
				}
				SetTextVisible(true, "PAUSETEXT1");
				SetTextVisible(true, "PAUSETEXT2");
			}
			else {
				if (GamePasueSound) {
					resumesound.play();
					GamePasueSound = false;
				}
				SetTextVisible(false, "PAUSETEXT1");
				SetTextVisible(false, "PAUSETEXT2");
			}
			UpdateText();
			rTexture.display();
			window.clear();
			window.draw(sf::Sprite(rTexture.getTexture()));
			window.display();
		}
	}
}