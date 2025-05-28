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

#include <ctre.hpp>

int main()
{
	kairos::Timestep timestep;
	timestep.setStep(1.0f / 500.0f);
	timestep.setMaxAccumulation(1.0f / 40.0f);

	music.play();
	music.setLooping(true);

	BgColorInitColor();
	MarioInit();
	ViewInit();
	LevelInit();
	SetMarioPosition(320, 416);

	PiranhaGroundAnimationInit();
	GoombaAnimationInit();
	SpinyAnimationInit();

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
		//Check when to generate map
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
			SpinyMovement(dt);
			setView(dt);
		}
		CheckLevelAvaliable();
		LevelUpdatePos();
		updateView();
		BgColorInitPos();
		CheckPiranhaGroundCollision();
		CheckGoombaCollision();
		CheckSpinyCollision();
		TimeVisibleGoombaDeath();

		updateAnimation();

		rTexture.clear();
		rTexture.setView(view);
		window.setView(viewwin);
		rTexture.draw(Backgroundcolor);
		LevelDraw();
		DrawEnemy();
		DrawGoombaDeath();
		if (CanMarioControl) rTexture.draw(mario);
		else rTexture.draw(mariodeath);
		rTexture.display();
		window.clear();
		window.draw(sf::Sprite(rTexture.getTexture()));
		window.display();
	}
}