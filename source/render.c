

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

void drawImage(char *path, int x, int y, int w, int h, int toX, int toY, int toW, int toH, bool isFlipX, bool isFlipY, int angle, float anchorX, float anchorY)
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
    int indentX = toW * anchorX;
    int indentY = toH * anchorY;
    SDL_Rect srcRect = {x, y, w, h};
    SDL_Rect sdtRect = {toX - indentX, toY - indentY, toW, toH};
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (isFlipX) flip |= SDL_FLIP_HORIZONTAL;
    if (isFlipY) flip |= SDL_FLIP_VERTICAL;
    SDL_Point point = {toW * anchorX, toW * anchorY};
    SDL_RenderCopyEx(renderer, imageTexture, &srcRect, &sdtRect, angle, &point, flip);
    SDL_DestroyTexture(imageTexture);
    SDL_FreeSurface(imageSurface);
    if (automatic) SDL_RenderPresent(renderer);
}

void drawText(char *text, int toX, int toY, char *font, int size, bool isFlipX, bool isFlipY, int angle, float anchorX, float anchorY)
{
    font = strlen(font) > 0 ? font : "alkatip.ttf";
    size = get_min(get_max(size, 1), 100);
    TTF_Font *ttf = TTF_OpenFont(font, size);
    assert(ttf != NULL, "ttf open failed!");
    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
    SDL_Color color = {r, g, b, a};
    SDL_Surface *textSurface = TTF_RenderUTF8_Blended(ttf, text, color);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    int textureW, textureH;
    int windowW, windowH;
    SDL_QueryTexture(textTexture, NULL, NULL, &textureW, &textureH);
    SDL_GetWindowSize(window, &windowW, &windowH);
    toX = get_min(get_max(toX, 0), windowW);
    toY = get_min(get_max(toY, 0), windowH);
    int indentX = textureW * anchorX;
    int indentY = textureH * anchorY;
    SDL_Rect srcRect = {0, 0, textureW, textureH};
    SDL_Rect sdtRect = {toX - indentX, toY - indentY, textureW, textureH};
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (isFlipX) flip |= SDL_FLIP_HORIZONTAL;
    if (isFlipY) flip |= SDL_FLIP_VERTICAL;
    SDL_Point point = {textureW * anchorX, textureH * anchorY};
    SDL_RenderCopyEx(renderer, textTexture, &srcRect, &sdtRect, angle, &point, flip);
    TTF_CloseFont(ttf);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    if (automatic) SDL_RenderPresent(renderer);
}

void doClear()
{
    SDL_RenderClear(renderer);
}

void setColor( int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void drawPoint(int x, int y)
{
    SDL_RenderDrawPoint(renderer, x, y);
    if (automatic) SDL_RenderPresent(renderer);
}

void drawLine(int x, int y, int toX, int toY)
{
    SDL_RenderDrawLine(renderer, x, y, toX, toY);
    if (automatic) SDL_RenderPresent(renderer);
}

void drawRect(int x, int y, int w, int h)
{
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderDrawRect(renderer, &rect);
    if (automatic) SDL_RenderPresent(renderer);
}

void fillRect(int x, int y, int w, int h)
{
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderFillRect(renderer, &rect);
    if (automatic) SDL_RenderPresent(renderer);
}


void renderTest()
{
    setColor(50, 50, 50, 255);
    doClear();
    //
    drawImage("./lua.png", 0, 0, 0, 0, 100, 350, 0, 0, false, false, 0, 0.5, 0.5);
    //
    char *text1 = "Hello World!";
    char *text2 = "!ﺎﻴﻧﯗﺩ ﺎﺑﺎﮬﺭﻪﻣ";
    char *font = "ukij.ttf";
    setColor(200, 0, 0, 255);
    drawText(text1, 100, 200, font, 24, true, false, 0, 0.5, 0.5);
    drawText(text1, 100, 225, font, 24, false, false, 0, 0.5, 0.5);
    drawText(text2, 100, 250, font, 24, false, false, 0, 0.5, 0.5);
    //
    setColor(0, 200, 0, 255);
    fillRect(150, 50, 50, 50);
    //
    setColor(0, 200, 0, 255);
    drawRect(250, 50, 50, 50);
    //
    setColor(0, 0, 200, 255);
    drawLine(10, 10, 300, 300);
    drawPoint(5, 5);


    // SDL_RenderSetScale
    // SDL_SetRenderDrawColor
    // SDL_RenderClear
    // SDL_RenderPresent

    // 
    printf("\nEND!");
}
