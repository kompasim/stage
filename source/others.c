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

void printRect(SDL_Rect rect)
{
    printf("RECT: x = %d, y = %d, w = %d, h = %d", rect.x, rect.y, rect.h, rect.h);
}

void saveScreenshot(const char *path, int w, int h)
{
    int a, b;
    SDL_GetWindowSize(window, &a, &b);
    w = w > 0 ? w : a;
    h = h > 0 ? h : b;
    const Uint32 format = SDL_PIXELFORMAT_ARGB8888;
    SDL_Surface *s = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, format);
    SDL_RenderReadPixels(renderer, NULL, format, s->pixels, s->pitch);
    SDL_SaveBMP(s, path);
    SDL_FreeSurface(s);
}

