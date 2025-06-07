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

	float delta_initx = 0.0f;
	AddText("SCORE", "", 32, 40);
	AddText("SCORETEXT", "SCORE", 32, 24);
	AddText("FPS", "", 0, 464);

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>())
				window.close();
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
		prev_initx = initx;
		fpsGame.update();
		timestep.addFrame();
		while (timestep.isUpdateRequired()) {
			const float dt = timestep.getStepAsFloat() * 50.0f;
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
		UpdateText();
		rTexture.display();
		window.clear();
		window.draw(sf::Sprite(rTexture.getTexture()));
		window.display();
	}
}