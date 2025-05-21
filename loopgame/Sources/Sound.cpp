#include <SFML/Audio.hpp>
#include "../Headers/Sound.hpp"

//Sound
sf::SoundBuffer jumpbuffer("Resources/Sound/jump.wav");
sf::Sound jump(jumpbuffer);
sf::SoundBuffer deathbuffer("Resources/Sound/mario_death.mp3");
sf::Sound death(deathbuffer);

//Music
sf::Music music("Resources/Music/musicgame.ogg");