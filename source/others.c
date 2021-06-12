// others

#include "head.h"

void setClipboard(char *txt)
{
    SDL_SetClipboardText(txt);
}

void getClipboard()
{
    char *txt = SDL_GetClipboardText();
}

void doDelay(int time)
{
    SDL_Delay(time);
}

uint32_t getTick()
{
    return SDL_GetTicks();
}

