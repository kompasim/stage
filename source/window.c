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

void setTitle(char *title)
{
    SDL_SetWindowTitle(window, title);
}

void getTitle()
{
    const char *title = SDL_GetWindowTitle(window);
}

void setPosition(int x, int y)
{
    SDL_SetWindowPosition(window, x, y);
}

void getPosition()
{
    int x, y;
    SDL_GetWindowPosition(window, &x, &y);
}

void setSize(int w, int h)
{
    SDL_SetWindowSize(window, w, h);
}

void getSize()
{
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
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

void setIcon(char *path)
{
    SDL_Surface *icon = IMG_Load(path);
    SDL_SetWindowIcon(window, icon);
}

void setOpacity(float opacity)
{
    SDL_SetWindowOpacity(window, opacity);
}
