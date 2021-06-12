

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <direct.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

extern SDL_Renderer *renderer;
extern SDL_Window *window;
extern bool automatic;

void drawImage(char *path, int x, int y, int w, int h, int toX, int toY, int toW, int toH)
{
    SDL_Surface *imageSurface = IMG_Load(path);
    SDL_Texture *imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    int textureW, textureH;
    int windowW, windowH;
    SDL_QueryTexture(imageTexture, NULL, NULL, &textureW, &textureH);
    SDL_GetWindowSize(window, &windowW, &windowH);
    x = get_min(get_max(x, 0), textureW);
    y = get_min(get_max(y, 0), textureH);
    w = get_min(get_max(w, 0), textureW);
    h = get_min(get_max(h, 0), textureH);
    int leftW = (textureW - x);
    int leftH = (textureH - y);
    w = w > 0 ? w : leftW;
    h = h > 0 ? h : leftH;
    toX = get_min(get_max(toX, 0), windowW);
    toY = get_min(get_max(toY, 0), windowH);
    toW = get_min(get_max(toW, 0), windowW);
    toH = get_min(get_max(toH, 0), windowH);
    toW = toW > 0 ? toW : leftW;
    toH = toH > 0 ? toH : leftH;
    SDL_Rect srcRect = {x, y, w, h};
    SDL_Rect sdtRect = {toX, toY, toW, toH};
    SDL_RenderCopy(renderer, imageTexture, &srcRect, &sdtRect);
    SDL_DestroyTexture(imageTexture);
    SDL_FreeSurface(imageSurface);
    if (automatic) SDL_RenderPresent(renderer);
}

void drawText(char *text, int r, int g, int b, int a, int toX, int toY, char *font, int size)
{
    font = strlen(font) > 0 ? font : "alkatip.ttf";
    size = get_min(get_max(size, 1), 100);
    TTF_Font *ttf = TTF_OpenFont(font, size);
    assert(ttf != NULL, "ttf open failed!");
    SDL_Color color = {r, g, b, a};
    SDL_Surface *textSurface = TTF_RenderUTF8_Blended(ttf, text, color);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    int textureW, textureH;
    int windowW, windowH;
    SDL_QueryTexture(textTexture, NULL, NULL, &textureW, &textureH);
    SDL_GetWindowSize(window, &windowW, &windowH);
    toX = get_min(get_max(toX, 0), windowW);
    toY = get_min(get_max(toY, 0), windowH);
    SDL_Rect srcRect = {0, 0, textureW, textureH};
    SDL_Rect sdtRect = {toX, toY, textureW, textureH};
    SDL_RenderCopy(renderer, textTexture, &srcRect, &sdtRect);
    TTF_CloseFont(ttf);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    if (automatic) SDL_RenderPresent(renderer);
}

void draw()
{

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);


    SDL_SetRenderDrawColor(renderer, 50, 50, 200, 255);
    SDL_Rect rect1 = {200, 10, 50, 50};
    SDL_RenderDrawRect(renderer, &rect1);
    SDL_RenderPresent(renderer);

    // SDL_RenderDrawLine
    // SDL_RenderDrawPoint
    // SDL_RenderDrawRect

    // SDL_RenderFillRect

    // SDL_RenderSetScale
    // SDL_SetRenderDrawColor
    // SDL_RenderClear
    // SDL_RenderPresent

    // 





    SDL_Rect rect2 = {200, 100, 50, 50};
    SDL_SetRenderDrawColor(renderer, 50, 200, 50, 255);
    SDL_RenderFillRect(renderer, &rect2);
    SDL_RenderPresent(renderer);
    printf("\nEND!");
}
