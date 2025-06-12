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
#include "Headers/Scenes/Mainmenu.hpp"
#include "Headers/Scenes/Options.hpp"
#include "Headers/Scenes/Totalscore.hpp"

#include <ctre.hpp>

int main()
{
	//Icon
	sf::Image icon;
	icon.loadFromFile("icon.png");
	window.setIcon(icon);

	//Mainmenu
	SetMainmenuPos();

	//Options
	SetOptionsPos();

	std::string lineoptions;
	std::ifstream inputOptionsFile("options.txt");

	while (std::getline(inputOptionsFile, lineoptions)) {
		for (auto& match : ctre::search_all<"Music=(.*)">(lineoptions)) {
			musicvolume = match.get<1>().to_number();
		}
		for (auto& match : ctre::search_all<"Sound=(.*)">(lineoptions)) {
			soundvolume = match.get<1>().to_number();
		}
	}
	inputOptionsFile.close();

	AddText("MUSIC_VOLUME", "", 128 + 92 + 16 + 5, 136);
	AddText("SOUND_VOLUME", "", 128 + 92 + 16 + 5, 182);

	//TotalScore
	SetTotalScorePos();

	AddText("TOTALSCORE", "", 240, 200);

	//Gameplay

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
			if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && musicvolume > 0 && musicleftcanpress) {
					musicvolume -= 10;
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && musicvolume < 100 && musicrightcanpress) {
					musicvolume += 10;
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && soundvolume > 0 && soundleftcanpress) {
					soundvolume -= 10;
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && soundvolume < 100 && soundrightcanpress) {
					soundvolume += 10;
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && exitoptionscanpress) {
					CurrentScene = 0;
					std::ofstream outputOptionFile("options.txt");

					if (outputOptionFile.is_open()) {
						outputOptionFile << "Music=" << musicvolume << "\n";
						outputOptionFile << "Sound=" << soundvolume << "\n";
						outputOptionFile.close();
					}
				}
			}
		}

		music.setVolume(musicvolume);
		mainmenumusic.setVolume(musicvolume);
		totalscoremusic.setVolume(musicvolume);

		jump.setVolume(soundvolume);
		death.setVolume(soundvolume);
		goombadeath.setVolume(soundvolume);
		speedup.setVolume(soundvolume);
		pausesound.setVolume(soundvolume);
		resumesound.setVolume(soundvolume);

		if (CurrentScene == 0) {
			if (!(mainmenumusic.getStatus() == sf::Music::Status::Playing) && !BlackBackgroundTrigger) {
				blackscreen1[0].color = blackscreen1[1].color = blackscreen1[2].color = blackscreen1[3].color = sf::Color(0, 0, 0, 0);
				mainmenumusic.play();
			}
			
			exitoptionscanpress = false;

			ActiveButtonMainMenu();

			timestep.addFrame();
			while (timestep.isUpdateRequired()) {
				float dt{ timestep.getStepAsFloat() * 50.0f };
				BlackScreenProcess(BlackBackgroundTrigger, dt, started, blackscreen1);
			}

			if (started >= 255) {
				mainmenumusic.stop();
				CurrentScene = 2;
				started = 0;
				BlackBackgroundTrigger = false;
			}
			
			updateView();
			rTexture.setView(view);
			window.setView(viewwin);

			window.clear();
			rTexture.clear();
			DrawMainMenu();
			rTexture.display();

			window.draw(sf::Sprite(rTexture.getTexture()));
			window.display();
		}

		else if (CurrentScene == 1) {
			if (!(mainmenumusic.getStatus() == sf::Music::Status::Playing) && !BlackBackgroundTrigger) mainmenumusic.play();
			updateView();
			rTexture.setView(view);
			window.setView(viewwin);

			EditText(std::to_string(musicvolume), "MUSIC_VOLUME");
			EditText(std::to_string(soundvolume), "SOUND_VOLUME");

			SetTextVisible(false, "SCORETEXT");
			SetTextVisible(false, "PAUSETEXT1");
			SetTextVisible(false, "PAUSETEXT2");
			SetTextVisible(false, "SCORE");
			SetTextVisible(false, "FPS");
			SetTextVisible(false, "TOTALSCORE");
			SetTextVisible(true, "MUSIC_VOLUME");
			SetTextVisible(true, "SOUND_VOLUME");

			ActiveButtonOptions();

			window.clear();
			rTexture.clear();
			DrawOptions();
			UpdateText();

			rTexture.display();

			window.draw(sf::Sprite(rTexture.getTexture()));
			window.display();
		}

		else if (CurrentScene == 3) {
			if (!(totalscoremusic.getStatus() == sf::Music::Status::Playing) && !BlackBackgroundTrigger) {
				blackscreen1[0].color = blackscreen1[1].color = blackscreen1[2].color = blackscreen1[3].color = sf::Color(0, 0, 0, 0);
				totalscoremusic.play();
			}
			SetTextVisible(false, "SCORETEXT");
			SetTextVisible(false, "PAUSETEXT1");
			SetTextVisible(false, "PAUSETEXT2");
			SetTextVisible(false, "SCORE");
			SetTextVisible(false, "FPS");
			SetTextVisible(false, "MUSIC_VOLUME");
			SetTextVisible(false, "SOUND_VOLUME");
			SetTextVisible(true, "TOTALSCORE");

			EditText("Score:"+std::to_string(scoregame)+"00", "TOTALSCORE");

			ActiveTotalScore();

			timestep.addFrame();
			while (timestep.isUpdateRequired()) {
				float dt{ timestep.getStepAsFloat() * 50.0f };
				BlackScreenProcess(BlackBackgroundTrigger, dt, started, blackscreen1);
			}

			if (started >= 255) {
				totalscoremusic.stop();
				scoregame = 0;
				CurrentScene = 2;
				started = 0;
				BlackBackgroundTrigger = false;
			}

			window.clear();
			rTexture.clear();
			rTexture.draw(totalscorebg);
			UpdateText();
			TotalScoreDraw();
			rTexture.draw(blackscreen1);

			rTexture.display();

			window.draw(sf::Sprite(rTexture.getTexture()));
			window.display();
		}

		else if (CurrentScene == 2) {
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
				CurrentScene = 3;
				SetMarioPosition(320, 416);
				MarioDeathClock.reset();
				processdeath = false;
				CanMarioControl = true;
				initx = 320.0f;
				speedtime = 2.0f;
				prev_speedtime = 2.0f;
				DeleteAllLevel();
				LevelInit();
				MarioDirection = FirstMarioDirection;
				Gameclock.reset();
			}

			SetTextVisible(false, "MUSIC_VOLUME");
			SetTextVisible(false, "SOUND_VOLUME");
			SetTextVisible(false, "TOTALSCORE");
			SetTextVisible(true, "SCORETEXT");
			SetTextVisible(true, "SCORE");
			SetTextVisible(true, "FPS");

			if(scoregame != 0) EditText(std::to_string(scoregame) + "00", "SCORE");
			else EditText(std::to_string(scoregame), "SCORE");
			EditText("FPS: " + std::to_string(static_cast<int>(fpsGame.getFps())), "FPS");

			timestep.pause();

			prev_initx = initx;
			fpsGame.update();

			//Check when to generate map
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