// bridge

#include "head.h"

Bridge *Bridge_new()
{
    return malloc(sizeof(Bridge));
}

void Bridge_create(Bridge *this)
{
    this->L = luaL_newstate();
    luaL_openlibs(this->L);
}

void Bridge_run(Bridge *this, char *path)
{
    luaL_dofile(this->L, path);
}

void Bridge_call(Bridge *this, char *funcName)
{
    lua_getglobal(this->L, funcName);
    lua_pcall(this->L, 0, 0, 0);
}

void Bridge_release(Bridge *this)
{
    lua_close(this->L);
}

void Lua_registerTableFunc(lua_State *L, char *key, lua_CFunction value)
{
    lua_pushstring(L, key);
    lua_pushcclosure(L, value, 0);
    lua_settable(L, -3);
}

void Bridge_registerTableFunc(Bridge *this, char *key, lua_CFunction value)
{
    Lua_registerTableFunc(this->L, key, value);
}

void Lua_registerTableInt(lua_State *L, char *key, int value)
{
    lua_pushstring(L, key);
    lua_pushinteger(L, value);
    lua_settable(L, -3);
}

void Bridge_registerTableInt(Bridge *this, char *key, int value)
{
    Lua_registerTableInt(this->L, key, value);
}

void Lua_registerTableNum(lua_State *L, char *key, double value)
{
    lua_pushstring(L, key);
    lua_pushnumber(L, value);
    lua_settable(L, -3);
}

void Bridge_registerTableNum(Bridge *this, char *key, double value)
{
    Lua_registerTableNum(this->L, key, value);
}

void Lua_registerRectTable(lua_State *L, SDL_Rect rect)
{
    lua_newtable(L);
    Lua_registerTableNum(L, "x", rect.x);
    Lua_registerTableNum(L, "y", rect.y);
    Lua_registerTableNum(L, "w", rect.w);
    Lua_registerTableNum(L, "h", rect.h);
}


//////////////////////////////////////////////////// event ////////////////////////////////////////////////////////////////

void Bridge_notifyNoArgs(Bridge *this, const char *eventName)
{
    const char *funcName = "Stage_handle";
    lua_getglobal(this->L, funcName);
    lua_pushstring(this->L, eventName);
    lua_pcall(this->L, 1, 0, 0);
}

void Bridge_notifyWithInt(Bridge *this, const char *eventName, int value)
{
    const char *funcName = "Stage_handle";
    lua_getglobal(this->L, funcName);
    lua_pushstring(this->L, eventName);
    lua_pushinteger(this->L, value);
    lua_pcall(this->L, 2, 0, 0);
}

void Bridge_notifyWithString(Bridge *this, const char *eventName, const char *value)
{
    const char *funcName = "Stage_handle";
    lua_getglobal(this->L, funcName);
    lua_pushstring(this->L, eventName);
    lua_pushstring(this->L, value);
    lua_pcall(this->L, 2, 0, 0);
}

void Bridge_notifyWithPoint(Bridge *this, const char *eventName, SDL_Point point)
{
    const char *funcName = "Stage_handle";
    lua_getglobal(this->L, funcName);
    lua_pushstring(this->L, eventName);
    lua_newtable(this->L);
    Bridge_registerTableInt(this, "x", point.x);
    Bridge_registerTableInt(this, "y", point.y);
    lua_pcall(this->L, 2, 0, 0);
}

//////////////////////////////////////////////////// test ////////////////////////////////////////////////////////////////

static int luaTestFunc(lua_State* L)
{
    double op1 = luaL_checknumber(L,1);
    double op2 = luaL_checknumber(L,2);
    printf("luaTestFunc...[%f] [%f]\n", op1, op2);
    lua_pushnumber(L,op1 - op2);
    return 1;
}

//////////////////////////////////////////////////// render ////////////////////////////////////////////////////////////////

static int luaSetAuto(lua_State* L)
{
    bool m = lua_toboolean(L,1);
    setAuto(m);
    return 0;  
}

static int luaSetBlend(lua_State* L)
{
    double m = luaL_checknumber(L,1);
    setBlend(m);
    return 0;  
}

static int luaDoRender(lua_State* L)
{
    doRender();
    return 0;  
}

static int luaDrawImage(lua_State* L)
{
    const char *path = luaL_checkstring(L, 1);
    double x = luaL_checknumber(L,2);
    double y = luaL_checknumber(L,3);
    double w = luaL_checknumber(L,4);
    double h = luaL_checknumber(L,5);
    double toX = luaL_checknumber(L,6);
    double toY = luaL_checknumber(L,7);
    double toW = luaL_checknumber(L,8);
    double toH = luaL_checknumber(L,9);
    bool isFlipX = lua_toboolean(L,10);
    bool isFlipY = lua_toboolean(L,11);
    bool angle = luaL_checknumber(L,12);
    double anchorX = luaL_checknumber(L,13);
    double anchorY = luaL_checknumber(L,14);
    drawImage(path, x, y, w, h, toX, toY, toW, toH, isFlipX, isFlipY, angle, anchorX, anchorY);
    return 0;  
}

static int luaDrawText(lua_State* L)
{
    const char *text = luaL_checkstring(L, 1);
    double x = luaL_checknumber(L,2);
    double y = luaL_checknumber(L,3);
    double w = luaL_checknumber(L,4);
    double h = luaL_checknumber(L,5);
    double toX = luaL_checknumber(L,6);
    double toY = luaL_checknumber(L,7);
    double toW = luaL_checknumber(L,8);
    double toH = luaL_checknumber(L,9);
    const char *font = luaL_checkstring(L, 10);
    double size = luaL_checknumber(L,11);
    bool isFlipX = lua_toboolean(L,12);
    bool isFlipY = lua_toboolean(L,13);
    bool angle = luaL_checknumber(L,14);
    double anchorX = luaL_checknumber(L,15);
    double anchorY = luaL_checknumber(L,16);
    drawText(text, x, y, w, h, toX, toY, toW, toH, font, size, isFlipX, isFlipY, angle, anchorX, anchorY);
    return 0;  
}

static int luaDoClear(lua_State* L)
{
    doClear();
    return 0;  
}

static int luaSetColor(lua_State* L)
{
    double r = luaL_checknumber(L,1);
    double g = luaL_checknumber(L,2);
    double b = luaL_checknumber(L,3);
    double a = luaL_checknumber(L,4);
    setColor(r, g, b, a);
    return 0;
}

static int luaGetColor(lua_State* L)
{
    Uint8 r, g, b, a;
    getColor(&r, &g, &b, &a);
    lua_newtable(L);
    Lua_registerTableInt(L, "r", r);
    Lua_registerTableInt(L, "g", g);
    Lua_registerTableInt(L, "b", b);
    Lua_registerTableInt(L, "a", a);
    return 1;
}

static int luaSetScale(lua_State* L)
{
    double x = luaL_checknumber(L,1);
    double y = luaL_checknumber(L,2);
    setScale(x, y);
    return 0;
}

static int luaGetScale(lua_State* L)
{
    float x, y;
    getScale(&x, &y);
    lua_newtable(L);
    Lua_registerTableNum(L, "x", x);
    Lua_registerTableNum(L, "y", y);
    return 1;
}

static int luaSetPort(lua_State* L)
{
    double x = luaL_checknumber(L,1);
    double y = luaL_checknumber(L,2);
    double w = luaL_checknumber(L,3);
    double h = luaL_checknumber(L,4);
    setPort(x, y, w, h);
    return 0;
}

static int luaGetPort(lua_State* L)
{
    SDL_Rect rect = getPort();
    Lua_registerRectTable(L, rect);
    return 1;
}

static int luaSetClip(lua_State* L)
{
    double x = luaL_checknumber(L,1);
    double y = luaL_checknumber(L,2);
    double w = luaL_checknumber(L,3);
    double h = luaL_checknumber(L,4);
    setClip(x, y, w, h);
    return 0;
}

static int luaGetClip(lua_State* L)
{
    SDL_Rect rect = getClip();
    Lua_registerRectTable(L, rect);
    return 1;
}

static int luaDrawPoint(lua_State* L)
{
    double x = luaL_checknumber(L,1);
    double y = luaL_checknumber(L,2);
    drawPoint(x, y);
    return 0;
}

static int luaDrawLine(lua_State* L)
{

    double x = luaL_checknumber(L,1);
    double y = luaL_checknumber(L,2);
    double toX = luaL_checknumber(L,3);
    double toY = luaL_checknumber(L,4);
    drawLine(x, y, toX, toY);
    return 0;
}

static int luaDrawRect(lua_State* L)
{
    double x = luaL_checknumber(L,1);
    double y = luaL_checknumber(L,2);
    double w = luaL_checknumber(L,3);
    double h = luaL_checknumber(L,4);
    drawRect(x, y, w, h);
    return 0;
}

static int luaFillRect(lua_State* L)
{
    double x = luaL_checknumber(L,1);
    double y = luaL_checknumber(L,2);
    double w = luaL_checknumber(L,3);
    double h = luaL_checknumber(L,4);
    fillRect(x, y, w, h);
    return 0;
}

//////////////////////////////////////////////////// audio ////////////////////////////////////////////////////////////////

static int luaInitAudio(lua_State* L)
{
    initAudio();
    return 0;
}

static int luaPlayMusic(lua_State* L)
{
    const char *path = luaL_checkstring(L, 1);
    double volume = luaL_checknumber(L,2);
    playMusic(path, volume);
    return 0;
}

static int luaPlaySound(lua_State* L)
{
    const char *path = luaL_checkstring(L, 1);
    double volume = luaL_checknumber(L,2);
    playSound(path, volume);
    return 0;
}

static int luaPauseAudio(lua_State* L)
{
    pauseAudio();
    return 0;
}

static int luaResumeAudio(lua_State* L)
{
    unpauseAudio();
    return 0;
}

static int luaEndAudio(lua_State* L)
{
    endAudio();
    return 0;
}

//////////////////////////////////////////////////// window ////////////////////////////////////////////////////////////////


static int luaShow(lua_State* L)
{
    show();
    return 0;
}

static int luaHide(lua_State* L)
{
    hide();
    return 0;
}

static int luaMaximaze(lua_State* L)
{
    maximaze();
    return 0;
}

static int luaMinimaze(lua_State* L)
{
    minimaze();
    return 0;
}

static int luaSetTitle(lua_State* L)
{
    const char *title = luaL_checkstring(L, 1);
    setTitle(title);
    return 0;
}

static int luaGetTitle(lua_State* L)
{
    const char *title = getTitle();
    lua_pushstring(L, title);
    return 1;
}

static int luaSetPosition(lua_State* L)
{
    double x = luaL_checknumber(L,1);
    double y = luaL_checknumber(L,2);
    setPosition(x, y);
    return 0;
}

static int luaGetPosition(lua_State* L)
{
    int x, y;
    getPosition(&x, &y);
    lua_newtable(L);
    Lua_registerTableNum(L, "x", x);
    Lua_registerTableNum(L, "y", y);
    return 1;
}

static int luaSetSize(lua_State* L)
{
    double w = luaL_checknumber(L,1);
    double h = luaL_checknumber(L,2);
    setSize(w, h);
    return 0;
}

static int luaGetSize(lua_State* L)
{
    int w, h;
    getSize(&w, &h);
    lua_newtable(L);
    Lua_registerTableNum(L, "w", w);
    Lua_registerTableNum(L, "h", h);
    return 1;
}

static int luaSetFullscreen(lua_State* L)
{
    bool isFullscreen = lua_toboolean(L, 1);
    setFullscreen(isFullscreen);
    return 0;
}

static int luaShowCursor(lua_State* L)
{
    bool isShow = lua_toboolean(L, 1);
    showCursor(isShow);
    return 0;
}

static int luaSetCursor(lua_State* L)
{
    int cursor = luaL_checkinteger(L, 1);
    setCursor(cursor);
    return 0;
}

static int luaSetIcon(lua_State* L)
{
    const char *path = luaL_checkstring(L, 1);
    setIcon(path);
    return 0;
}

static int luaSetOpacity(lua_State* L)
{
    double opacity = luaL_checknumber(L, 1);
    setOpacity(opacity);
    return 0;
}

//////////////////////////////////////////////////// stage ////////////////////////////////////////////////////////////////

static int luaDoExit(lua_State* L)
{
    Stage_stop(stage);
    return 0;
}

static int luaGetVersion(lua_State* L)
{
    const char *text = getVersion();
    lua_pushstring(L, text);
    return 1;
}

static int luaDoDelay(lua_State* L)
{
    double time = luaL_checknumber(L,1);
    doDelay(time);
    return 0;
}

static int luaGetTick(lua_State* L)
{
    uint32_t tick = getTick();
    lua_pushnumber(L, tick);
    return 1;
}

static int luaSetClipboard(lua_State* L)
{
    const char *text = luaL_checkstring(L, 1);
    setClipboard(text);
    return 0;
}

static int luaGetClipboard(lua_State* L)
{
    const char *text = getClipboard();
    lua_pushstring(L, text);
    return 1;
}

//////////////////////////////////////////////////// register ////////////////////////////////////////////////////////////////

void Bridge_register(Bridge *this)
{
    //
    // lua_register(this->L, "testFunc", luaTestFunc);
    // lua_register(this->L, "drawPoint", luaDrawPoint);
    // render
    lua_newtable(this->L);
    Bridge_registerTableFunc(this, "setAuto", luaSetAuto);
    Bridge_registerTableFunc(this, "setBlend", luaSetBlend);
    Bridge_registerTableFunc(this, "doRender", luaDoRender);
    Bridge_registerTableFunc(this, "drawImage", luaDrawImage);
    Bridge_registerTableFunc(this, "drawText", luaDrawText);
    Bridge_registerTableFunc(this, "doClear", luaDoClear);
    Bridge_registerTableFunc(this, "setColor", luaSetColor);
    Bridge_registerTableFunc(this, "getColor", luaGetColor);
    Bridge_registerTableFunc(this, "setScale", luaSetScale);
    Bridge_registerTableFunc(this, "getScale", luaGetScale);
    Bridge_registerTableFunc(this, "setPort", luaSetPort);
    Bridge_registerTableFunc(this, "getPort", luaGetPort);
    Bridge_registerTableFunc(this, "setClip", luaSetClip);
    Bridge_registerTableFunc(this, "getClip", luaGetClip);
    Bridge_registerTableFunc(this, "drawPoint", luaDrawPoint);
    Bridge_registerTableFunc(this, "drawLine", luaDrawLine);
    Bridge_registerTableFunc(this, "drawRect", luaDrawRect);
    Bridge_registerTableFunc(this, "fillRect", luaFillRect);
    lua_setglobal(this->L, "render");
    // audio
    lua_newtable(this->L);
    Bridge_registerTableFunc(this, "initAudio", luaInitAudio);
    Bridge_registerTableFunc(this, "playMusic", luaPlayMusic);
    Bridge_registerTableFunc(this, "playSound", luaPlaySound);
    Bridge_registerTableFunc(this, "pauseAudio", luaPauseAudio);
    Bridge_registerTableFunc(this, "resumeAudio", luaResumeAudio);
    Bridge_registerTableFunc(this, "endAudio", luaEndAudio);
    lua_setglobal(this->L, "audio");
    // window
    lua_newtable(this->L);
    Bridge_registerTableFunc(this, "show", luaShow);
    Bridge_registerTableFunc(this, "hide", luaHide);
    Bridge_registerTableFunc(this, "maximaze", luaMaximaze);
    Bridge_registerTableFunc(this, "minimaze", luaMinimaze);
    Bridge_registerTableFunc(this, "setTitle", luaSetTitle);
    Bridge_registerTableFunc(this, "getTitle", luaGetTitle);
    Bridge_registerTableFunc(this, "setPosition", luaSetPosition);
    Bridge_registerTableFunc(this, "getPosition", luaGetPosition);
    Bridge_registerTableFunc(this, "setSize", luaSetSize);
    Bridge_registerTableFunc(this, "getSize", luaGetSize);
    Bridge_registerTableFunc(this, "setFullscreen", luaSetFullscreen);
    Bridge_registerTableFunc(this, "showCursor", luaShowCursor);
    Bridge_registerTableFunc(this, "setCursor", luaSetCursor);
    Bridge_registerTableFunc(this, "setIcon", luaSetIcon);
    Bridge_registerTableFunc(this, "setOpacity", luaSetOpacity);
    lua_setglobal(this->L, "window");
    // stage
    lua_newtable(this->L);
    Bridge_registerTableFunc(this, "getVersion", luaGetVersion);
    Bridge_registerTableFunc(this, "doExit", luaDoExit);
    Bridge_registerTableFunc(this, "doDelay", luaDoDelay);
    Bridge_registerTableFunc(this, "getTick", luaGetTick);
    Bridge_registerTableFunc(this, "setClipboard", luaSetClipboard);
    Bridge_registerTableFunc(this, "getClipboard", luaGetClipboard);
    lua_setglobal(this->L, "stage");

}
