// stage

#include "head.h"

Stage *Stage_new()
{
    return malloc(sizeof(Stage));
}


void Stage_create(Stage *this, char *title, int width, int height, int flag)
{
    do_assert(TTF_Init() == 0, "ttf init failed!");
    do_assert(SDL_Init(SDL_INIT_EVERYTHING) == 0, "sdl init failed!");
    this->window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        flag
    );
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    this->running = false;
}

bool Stage_running(Stage *this)
{
    return this->running;
}

void Stage_callLua(Stage *this, const char *func)
{
    char funcName[1024];
    sprintf(funcName, "Stage_%s", func);
    Bridge_call(bridge, funcName);
}

void Stage_start(Stage *this)
{
    this->running = true;
    testCode();
    Stage_callLua(this, "start");
}

void Stage_stop(Stage *this)
{
    Stage_callLua(this, "stop");
    this->running = false;
}

void Stage_release(Stage *this)
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void Stage_before(Stage *this)
{
    Stage_callLua(this, "before");
}

void Stage_handle(Stage *this ,SDL_Event event)
{
    if (event.type == SDL_QUIT)
    {
        Bridge_notifyNoArgs(bridge, "SDL_QUIT");
    }
    else if (event.type == SDL_WINDOWEVENT)
    {
        char *tp = "SDL_WINDOWEVENT_NONE";
        switch (event.window.event)
        {
        case SDL_WINDOWEVENT_SHOWN:
            tp = "SDL_WINDOWEVENT_SHOWN";
            break;
        case SDL_WINDOWEVENT_HIDDEN:
            tp = "SDL_WINDOWEVENT_HIDDEN";
            break;
        case SDL_WINDOWEVENT_EXPOSED:
            tp = "SDL_WINDOWEVENT_EXPOSED";
            break;
        case SDL_WINDOWEVENT_MOVED:
            tp = "SDL_WINDOWEVENT_MOVED";
            break;
        case SDL_WINDOWEVENT_RESIZED:
            tp = "SDL_WINDOWEVENT_RESIZED";
            break;
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            tp = "SDL_WINDOWEVENT_SIZE_CHANGED";
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            tp = "SDL_WINDOWEVENT_MINIMIZED";
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
            tp = "SDL_WINDOWEVENT_MAXIMIZED";
            break;
        case SDL_WINDOWEVENT_RESTORED:
            tp = "SDL_WINDOWEVENT_RESTORED";
            break;
        case SDL_WINDOWEVENT_ENTER:
            tp = "SDL_WINDOWEVENT_ENTER";
            break;
        case SDL_WINDOWEVENT_LEAVE:
            tp = "SDL_WINDOWEVENT_LEAVE";
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            tp = "SDL_WINDOWEVENT_FOCUS_GAINED";
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            tp = "SDL_WINDOWEVENT_FOCUS_LOST";
            break;
        case SDL_WINDOWEVENT_CLOSE:
            tp = "SDL_WINDOWEVENT_CLOSE";
            break;
        case SDL_WINDOWEVENT_TAKE_FOCUS:
            tp = "SDL_WINDOWEVENT_TAKE_FOCUS";
            break;
        case SDL_WINDOWEVENT_HIT_TEST:
            tp = "SDL_WINDOWEVENT_HIT_TEST";
            break;
        default:
            break;
        };
        Bridge_notifyWithString(bridge, "SDL_WINDOWEVENT", tp);
    }
    else if (event.type == SDL_CLIPBOARDUPDATE)
    {
        Bridge_notifyNoArgs(bridge, "SDL_CLIPBOARDUPDATE");
    }
    else if (event.type == SDL_DROPFILE)
    {
        Bridge_notifyWithString(bridge, "SDL_DROPFILE", event.drop.file);
    }
    else if (event.type == SDL_KEYDOWN)
    {
        const char *key = SDL_GetKeyName(event.key.keysym.sym);
        Bridge_notifyWithString(bridge, "SDL_KEYDOWN", key);
    }
    else if (event.type == SDL_KEYUP)
    {
        const char *key = SDL_GetKeyName(event.key.keysym.sym);
        Bridge_notifyWithString(bridge, "SDL_KEYUP", key);
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        Bridge_notifyWithInt(bridge, "SDL_MOUSEBUTTONDOWN", event.button.button);
    }
    else if (event.type == SDL_MOUSEBUTTONUP)
    {
        Bridge_notifyWithInt(bridge, "SDL_MOUSEBUTTONUP", event.button.button);
    }
    else if (event.type == SDL_MOUSEMOTION)
    {
        SDL_Point point = {event.button.x, event.button.y};
        Bridge_notifyWithPoint(bridge, "SDL_MOUSEMOTION", point);
    }
    else if (event.type == SDL_MOUSEWHEEL)
    {
        Bridge_notifyWithInt(bridge, "SDL_MOUSEWHEEL", event.wheel.y);
    }
}

void Stage_update(Stage *this)
{
    Stage_callLua(this, "update");
}

void Stage_render(Stage *this)
{
    Stage_callLua(this, "render");
}

void Stage_after(Stage *this)
{
    Stage_callLua(this, "after");
}
