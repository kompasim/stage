// others

#include "head.h"

const char *getVersion()
{
    return "0.0.1";
}

void doDelay(int time)
{
    SDL_Delay(time);
}

uint32_t getTick()
{
    return SDL_GetTicks();
}

void setClipboard(const char *txt)
{
    SDL_SetClipboardText(txt);
}

char *getClipboard()
{
    return SDL_GetClipboardText();
}

