/**
* 2D Audio
*
* Author: Jean-Louis Haywood
*
* Loads audio files to play on callback.
*/

#pragma once

void initSDLAudio();

/*| Insert MUSIC for infinitely looping background music,
| SOUND for everything else. 
| The filepath is relative to the executable.*/
int audio_set(unsigned char type, const char* filePath);

/*| Be sure to make the distinction between MUSIC and SOUND queues,
| INFINITE or -1 plays the audio infinitely,
| Playing a new MUSIC file cancels the previous song,
| Sounds, however can overlap channels safely.*/
void audio_play(unsigned char type, int audioNumber, int loops);