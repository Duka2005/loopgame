#pragma once
#ifndef SOUND_HPP
#define SOUND_HPP

#include <SFML/Audio.hpp>

extern sf::SoundBuffer jumpbuffer;
extern sf::Sound jump;
extern sf::SoundBuffer deathbuffer;
extern sf::Sound death;
extern sf::SoundBuffer goombadeathbuffer;
extern sf::Sound goombadeath;
extern sf::SoundBuffer speedupbuffer;
extern sf::Sound speedup;
extern sf::SoundBuffer pausesoundbuffer;
extern sf::Sound pausesound;
extern sf::SoundBuffer resumesoundbuffer;
extern sf::Sound resumesound;

extern sf::Music music;
extern sf::Music mainmenumusic;
extern sf::Music totalscoremusic;

#endif