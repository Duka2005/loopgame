#include <SFML/Graphics.hpp>
#include "Headers/Mario.hpp"
#include "Headers/Tileset.hpp"
#include "Headers/Window.hpp"
#include "Headers/Kairos.hpp"
#include "Headers/GenLevel.hpp"

int main()
{
	kairos::Timestep timestep;
	timestep.setStep(1.0f / 500.0f);
	timestep.setMaxAccumulation(1.0f / 40.0f);

	MarioInit();
	ViewInit();
	SetMarioPosition(32, 128);

	GenLevel();

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

		updateAnimation();

		rTexture.clear();
		for (const auto& i : obstacles) {
			rTexture.draw(i);
		}
		setView();
		rTexture.setView(view);
		window.setView(viewwin);
		rTexture.draw(mario);
		rTexture.display();
		window.clear();
		window.draw(sf::Sprite(rTexture.getTexture()));
		window.display();
	}
}