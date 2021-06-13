// window

#include "head.h"

extern SDL_Window *window;

void show()
{
    SDL_ShowWindow(window);
}

void hide()
{
    SDL_HideWindow(window);
}

void maximaze()
{
    SDL_MaximizeWindow(window);
}

void minimaze()
{
    SDL_MinimizeWindow(window);
}

void setTitle(const char *title)
{
    SDL_SetWindowTitle(window, title);
}

const char *getTitle()
{
    return SDL_GetWindowTitle(window);
}

void setPosition(int x, int y)
{
    SDL_SetWindowPosition(window, x, y);
}

void getPosition(int *x, int *y)
{
    int a, b;
    SDL_GetWindowPosition(window, &a, &b);
    *x = a;
    *y = b;
}

void setSize(int w, int h)
{
    SDL_SetWindowSize(window, w, h);
}

void getSize(int *w, int *h)
{
    int a, b;
    SDL_GetWindowSize(window, &a, &b);
    *w = a;
    *h = b;
}

void setFullscreen(bool isFullscreen)
{
    SDL_SetWindowFullscreen(window, isFullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0); 
}

void showCursor(bool isShow)
{
    SDL_ShowCursor(isShow ? 1 : 0);
}

void setCursor(int cursor)
{
    SDL_SetCursor(SDL_CreateSystemCursor(cursor));
}

void setIcon(const char *path)
{
    SDL_Surface *icon = IMG_Load(path);
    SDL_SetWindowIcon(window, icon);
}

void setOpacity(float opacity)
{
    SDL_SetWindowOpacity(window, opacity);
}
