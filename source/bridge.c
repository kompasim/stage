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

void Bridge_register(Bridge *this)
{
    //
}

void Bridge_run(Bridge *this, char *path)
{
    luaL_dofile(this->L, path);
}

void Bridge_release(Bridge *this)
{
    lua_close(this->L);
}
