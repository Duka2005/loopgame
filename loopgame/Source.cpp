#include <SFML/Graphics.hpp>
#include "Headers/Mario.hpp"
#include "Headers/Tileset.hpp"
#include "Headers/Window.hpp"
#include "Headers/Kairos.hpp"

int main()
{
	kairos::Timestep timestep;
	timestep.setStep(1.0f / 500.0f);
	timestep.setMaxAccumulation(1.0f / 40.0f);

	sf::RenderTexture rTexture({ 640, 480 });

	SetMarioPosition(32, 128);

	for (int i = 0; i < 6; ++i)
		addObstacleBlock(128 + i * 32.0f, 384.0f, 0, 64);
	addObstacleBlock(128.0f, 352.0f, 0, 64);
	addObstacleBlock(128.0f, 320.0f, 0, 64);
	addObstacleBlock(128.0f, 288.0f, 0, 64);
	addObstacleBlock(128.0f + 128.0f, 288.0f, 0, 64);
	addObstacleBlock(128.0f + 128.0f + 32.0f, 288.0f, 0, 64);
	addObstacleBlock(128.0f + 64.0f, 352.0f, 0, 64);

	addObstacleBlock(0.0f, 416.0f, 0, 0);
	addObstacleBlock(0.0f, 448.0f, 0, 32);
	for (int i = 0; i < 18; ++i) {
		addObstacleBlock(32.0f + i * 32.0f, 416.0f, 32, 0);
		addObstacleBlock(32.0f + i * 32.0f, 448.0f, 32, 32);
	}
	addObstacleBlock(32.0f + 18 * 32.0f, 416.0f, 64, 0);
	addObstacleBlock(32.0f + 18 * 32.0f, 448.0f, 64, 32);

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		timestep.addFrame();
		while (timestep.isUpdateRequired()) {
			float dt = timestep.getStepAsFloat() * 50.0f;
			MarioMovement(dt);
			MarioHorizonUpdate(dt);
			MarioVerticleUpdate(dt);
		}

		//marioCollisionLeft(mario, marioleft);
		//marioCollisionRight(mario, marioright);

		rTexture.clear();
		for (const auto& i : obstacles) {
			rTexture.draw(i);
		}
		rTexture.draw(mario);
		rTexture.display();
		window.clear();
		window.draw(sf::Sprite(rTexture.getTexture()));
		window.display();
	}
}