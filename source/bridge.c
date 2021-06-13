// bridge

#include "head.h"

typedef struct {
    lua_State* L;
} Bridge;

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

static int luaTestFunc(lua_State* L)
{
    double op1 = luaL_checknumber(L,1);
    double op2 = luaL_checknumber(L,2);
    printf("luaTestFunc...[%f] [%f]\n", op1, op2);
    lua_pushnumber(L,op1 - op2);
    return 1;
}

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

    return 0;
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

    return 0;
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


}