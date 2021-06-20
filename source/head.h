// head


#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <direct.h>
#include <stdlib.h>
#include <math.h>

#ifndef LUA_SCRIPT_LIB
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#define LUA_SCRIPT_LIB
#endif

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

// variables
#ifndef HEAD_VARIABLES

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
bool automatic = false;

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool running;
} Stage;
typedef struct {
    lua_State* L;
} Bridge;

Stage *stage = NULL;
Bridge *bridge = NULL;

#define HEAD_VARIABLES
#endif

// functions
#ifndef HEAD_FUNCTIONS

void Bridge_call(Bridge *, char *);
void Bridge_notifyNoArgs(Bridge *, const char *);
void Bridge_notifyWithInt(Bridge *, const char *, int);
void Bridge_notifyWithString(Bridge *, const char *, const char *);
void Bridge_notifyWithPoint(Bridge *, const char *, SDL_Point);

#define HEAD_FUNCTIONS
#endif