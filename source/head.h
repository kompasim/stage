// head

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <direct.h>
#include <stdlib.h>

#ifndef SIMPLE_SDL_AUDIO
#include "audio/audio.h"
#include "audio/audio.c"
#define SIMPLE_SDL_AUDIO
#endif

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
