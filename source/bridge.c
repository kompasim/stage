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

static int luaSetScale(lua_State* L)
{
    double x = luaL_checknumber(L,1);
    double y = luaL_checknumber(L,2);
    setScale(x, y);
    return 0;
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

static int luaSetClip(lua_State* L)
{
    double x = luaL_checknumber(L,1);
    double y = luaL_checknumber(L,2);
    double w = luaL_checknumber(L,3);
    double h = luaL_checknumber(L,4);
    setClip(x, y, w, h);
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

void Bridge_registerTableFunc(Bridge *this, char *key, lua_CFunction func)
{
    lua_pushstring(this->L, key);
    lua_pushcclosure(this->L, func, 0);
    lua_settable(this->L, -3);
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
    Bridge_registerTableFunc(this, "doClear", luaDoClear);
    Bridge_registerTableFunc(this, "setColor", luaSetColor);
    Bridge_registerTableFunc(this, "setScale", luaSetScale);

    Bridge_registerTableFunc(this, "setPort", luaSetPort);
    Bridge_registerTableFunc(this, "setClip", luaSetClip);
    Bridge_registerTableFunc(this, "drawPoint", luaDrawPoint);
    Bridge_registerTableFunc(this, "drawLine", luaDrawLine);
    Bridge_registerTableFunc(this, "drawRect", luaDrawRect);
    Bridge_registerTableFunc(this, "fillRect", luaFillRect);
    lua_setglobal(this->L, "render");


}