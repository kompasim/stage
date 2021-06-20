// audio

#include "head.h"

Mix_Music *sound = NULL;

void initAudio(void)
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}


void stopMusic()
{
    if (sound == NULL) return;
    Mix_HaltMusic();
    Mix_FreeMusic(sound);
    sound = NULL;
}

void playMusic(const char *filename, int loop)
{
    stopMusic();
    sound = Mix_LoadMUS(filename);
	Mix_PlayMusic(sound, loop); 
}

void resumeMusic()
{
    Mix_ResumeMusic();
}

void pauseMusic()
{
    Mix_PauseMusic();
}


bool playingMusic()
{
    return Mix_PlayingMusic();
}

bool pausedMusic()
{
    return Mix_PausedMusic();
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
