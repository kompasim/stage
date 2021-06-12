// render

#include "head.h"

extern SDL_Renderer *renderer;
extern bool automatic;

void setAuto(bool isAuto)
{
    automatic = isAuto;
}

void setBlend(int mode)
{
    SDL_SetRenderDrawBlendMode(renderer, mode);
}

void doRender()
{
    SDL_RenderPresent(renderer);
}

SDL_Point parseTexture(SDL_Texture *texture, int x, int y, int w, int h, int toX, int toY, int toW, int toH, float anchorX, float anchorY, SDL_Rect *src, SDL_Rect *dst)
{
    int textureW, textureH;
    SDL_QueryTexture(texture, NULL, NULL, &textureW, &textureH);
    x = get_min(get_max(x, 0), textureW);
    y = get_min(get_max(y, 0), textureH);
    w = get_min(get_max(w, 0), textureW);
    h = get_min(get_max(h, 0), textureH);
    int leftW = (textureW - x);
    int leftH = (textureH - y);
    w = w > 0 ? w : leftW;
    h = h > 0 ? h : leftH;
    toW = toW > 0 ? toW : leftW;
    toH = toH > 0 ? toH : leftH;
    int indentX = toW * anchorX;
    int indentY = toH * anchorY;
    (*src).x = x;
    (*src).y = y;
    (*src).w = w;
    (*src).h = h;
    (*dst).x = toX - indentX;
    (*dst).y = toY - indentY;
    (*dst).w = toW;
    (*dst).h = toH;
    SDL_Point point = {toW * anchorX, toW * anchorY};
    return point;
}

void drawImage(char *path, int x, int y, int w, int h, int toX, int toY, int toW, int toH, bool isFlipX, bool isFlipY, int angle, float anchorX, float anchorY)
{
    SDL_Texture *texture = IMG_LoadTexture(renderer, path);
    SDL_Rect srcRect, dstRect;
    SDL_Point point = parseTexture(texture, x, y, w, h, toX, toY, toW, toH, anchorX, anchorY, &srcRect, &dstRect);
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (isFlipX) flip |= SDL_FLIP_HORIZONTAL;
    if (isFlipY) flip |= SDL_FLIP_VERTICAL;
    SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, angle, &point, flip);
    SDL_DestroyTexture(texture);
    if (automatic) doRender();
}

void drawText(char *text, int x, int y, int w, int h, int toX, int toY, int toW, int toH, char *font, int size, bool isFlipX, bool isFlipY, int angle, float anchorX, float anchorY)
{
    font = strlen(font) > 0 ? font : "ukij.ttf";
    size = get_min(get_max(size, 1), 100);
    TTF_Font *ttf = TTF_OpenFont(font, size);
    assert(ttf != NULL, "ttf open failed!");
    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
    SDL_Color color = {r, g, b, a};
    SDL_Surface *surface = TTF_RenderUTF8_Blended(ttf, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect srcRect, dstRect;
    SDL_Point point = parseTexture(texture, x, y, w, h, toX, toY, toW, toH, anchorX, anchorY, &srcRect, &dstRect);
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (isFlipX) flip |= SDL_FLIP_HORIZONTAL;
    if (isFlipY) flip |= SDL_FLIP_VERTICAL;
    SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, angle, &point, flip);
    TTF_CloseFont(ttf);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    if (automatic) doRender();
}

void doClear()
{
    SDL_RenderClear(renderer);
    if (automatic) doRender();
}

void setColor( int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void getColor()
{
    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
}

void setScale(float scaleX, float scaleY)
{
    SDL_RenderSetScale(renderer, scaleX, scaleY);
}

void getScale()
{
    float x, y;
    SDL_RenderGetScale(renderer, &x, &y);
}

void setPort(int x, int y, int w, int h)
{
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderSetViewport(renderer, &rect);
}

void getPort()
{
    SDL_Rect rect;
    SDL_RenderGetViewport(renderer, &rect);
}

void setClip(int x, int y, int w, int h)
{
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderSetClipRect(renderer, &rect);
}

void getClip()
{
    SDL_Rect rect;
    SDL_RenderGetClipRect(renderer, &rect);
}


void drawPoint(int x, int y)
{
    SDL_RenderDrawPoint(renderer, x, y);
    if (automatic) doRender();
}

void drawLine(int x, int y, int toX, int toY)
{
    SDL_RenderDrawLine(renderer, x, y, toX, toY);
    if (automatic) doRender();
}

void drawRect(int x, int y, int w, int h)
{
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderDrawRect(renderer, &rect);
    if (automatic) doRender();
}

void fillRect(int x, int y, int w, int h)
{
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderFillRect(renderer, &rect);
    if (automatic) doRender();
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
    drawText(text1, 0, 0, 0, 0, 100, 200, 0, 0, font, 24, true, false, 0, 0.5, 0.5);
    drawText(text1, 50, 0, 0, 0, 100, 225, 0, 0, font, 24, false, false, 0, 0.5, 0.5);
    drawText(text2, 0, 0, 0, 0, 100, 250, 0, 0, font, 24, false, false, 0, 0.5, 0.5);
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
}
