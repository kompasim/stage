// audio

#include "head.h"

void initAudio(void)
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

void playMusic(const char *filename, int loop)
{
    Mix_Music *sound=Mix_LoadMUS(filename);
	Mix_PlayMusic(sound, loop); 
}

void pauseMusic()
{
    Mix_PauseMusic();
}

void resumeMusic()
{
    Mix_ResumeMusic();
}

bool playingMusic()
{
    return Mix_PlayingMusic();
}

bool volumeMusic(int volume)
{
    return Mix_VolumeMusic(volume);
}

void playSound(const char * filename, int loop)
{
    Mix_Chunk *sound=Mix_LoadWAV(filename);
    Mix_PlayChannel(-1, sound, loop);
}

void destroyAudio()
{
    Mix_CloseAudio();
}