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
	int scoregame = 0;

	sf::VertexArray blackscreen(sf::PrimitiveType::TriangleStrip, 4);
	blackscreen[0].color = blackscreen[1].color = blackscreen[2].color = blackscreen[3].color = sf::Color(0, 0, 0, 128);

	kairos::Timestep timestep;
	kairos::FpsLite fpsGame;
	timestep.setStep(1.0f / 500.0f);
	timestep.setMaxAccumulation(1.0f / 40.0f);

	music.play();
	music.setLooping(true);

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

		if (!GAME_PAUSE) {
			if (!Gameclock.isRunning()) Gameclock.start();
			if (!MarioDeathClock.isRunning() && (processdeath || isactive)) {
				MarioDeathClock.start();
				death.play();
			}
			if (!(music.getStatus() == sf::Music::Status::Playing) && !processdeath && !isactive) music.play();
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
			window.close();
		}

		EditText(std::to_string(scoregame) + "00", "SCORE");
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