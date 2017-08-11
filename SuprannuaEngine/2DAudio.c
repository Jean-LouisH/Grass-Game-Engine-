#include "SuprannuaEngine.h"

static Mix_Music* music[MAX_AUDIO_FILES];
static Mix_Chunk* sound[MAX_AUDIO_FILES];

static int storedMusic;
static int storedSound;

void initSDLAudio()
{
	SDL_Init(SDL_INIT_AUDIO);
	Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
	Mix_OpenAudio(44100, AUDIO_S16SYS, 2, pow(2, 11));
}

void audio_set(unsigned char type, const char* filePath)
{
	int i;

	if (type == MUSIC)
	{
		for (i = 0; i < MAX_AUDIO_FILES &&
			music[i] != NULL; i++)
		{
			;
		}

		if (i > storedMusic)
		{
			storedMusic = i;
		}

		music[i] = Mix_LoadMUS(filePath);
	}
	else if (type == SOUND)
	{
		for (i = 0; i < MAX_AUDIO_FILES &&
			sound[i] != NULL; i++)
		{
			;
		}

		if (i > storedSound)
		{
			storedSound = i;
		}

		sound[i] = Mix_LoadWAV(filePath);
	}
}

void audio_play(unsigned char type, int audioNumber, int loops)
{
	static currentMusic;

	if (type == MUSIC)
	{
		/*Halts existing music, or just starts when silent.*/
		if (Mix_PlayingMusic() && (currentMusic != audioNumber))
		{
			Mix_HaltMusic();
		}
		Mix_PlayMusic(music[audioNumber], loops);
		currentMusic = audioNumber;
	}
	else if (type == SOUND)
	{
		Mix_PlayChannel(-1, sound[audioNumber], loops);
	}
}