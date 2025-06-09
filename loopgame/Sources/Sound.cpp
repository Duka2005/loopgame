#include <SFML/Audio.hpp>
#include "../Headers/Sound.hpp"

//Sound
sf::SoundBuffer jumpbuffer("Resources/Sound/jump.wav");
sf::Sound jump(jumpbuffer);
sf::SoundBuffer deathbuffer("Resources/Sound/mario_death.mp3");
sf::Sound death(deathbuffer);
sf::SoundBuffer goombadeathbuffer("Resources/Sound/stomp.wav");
sf::Sound goombadeath(goombadeathbuffer);
sf::SoundBuffer speedupbuffer("Resources/Sound/speedup.mp3");
sf::Sound speedup(speedupbuffer);
sf::SoundBuffer pausesoundbuffer("Resources/Sound/pause.wav");
sf::Sound pausesound(pausesoundbuffer);
sf::SoundBuffer resumesoundbuffer("Resources/Sound/resume.wav");
sf::Sound resumesound(resumesoundbuffer);

//Music
sf::Music music("Resources/Music/musicgame.ogg");
sf::Music mainmenumusic("Resources/Music/mainmenu.mp3");