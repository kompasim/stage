// main

#include "head.h"
#include "tools.c"
#include "others.c"
#include "window.c"
#include "render.c"
#include "test.c"
#include "stage.c"
#include "bridge.c"

// config
const char *CONFIG_NAME = "./others/config.txt";

// args
char *windowTitle = "Stage";
int windowWidth = 480;
int windowHeight = 480;
bool windowCanResize = false;
bool windowNoBorder = false;
bool windowIsHidden = false;
bool windowOnTop = false;
bool windowSkipTask = false;
char *windowSizeState = "EMPTY";
char *luaScriptFile = "./scripts/stage.lua";
int framesPerSecond = 0;

uint32_t frameTime = 0;
Uint32 flag = 0;

// parse line
void parseLine(char *left, char *right)
{
    if (is_similar(left, "WINDOW_TITLE"))
        windowTitle = right;
    else if (is_similar(left, "WINDOW_WIDTH"))
        windowWidth = atoi(right);
    else if (is_similar(left, "WINDOW_HEIGHT"))
        windowHeight = atoi(right);
    else if (is_similar(left, "WINDOW_CAN_RESIZE"))
        windowCanResize = is_similar(right, "TRUE");
    else if (is_similar(left, "WINDOW_NO_BORDER"))
        windowNoBorder = is_similar(right, "TRUE");
    else if (is_similar(left, "WINDOW_IS_HIDDEN"))
        windowIsHidden = is_similar(right, "TRUE");
    else if (is_similar(left, "WINDOW_ON_TOP"))
        windowOnTop = is_similar(right, "TRUE");
    else if (is_similar(left, "WINDOW_SKIP_TASK"))
        windowSkipTask = is_similar(right, "TRUE");
    else if (is_similar(left, "IS_AUTO_RENDER"))
        automatic = is_similar(right, "TRUE");
    else if (is_similar(left, "WINDOW_SIZE_STATE"))
        windowSizeState = right;
    else if (is_similar(left, "LUA_SCRIPT_FILE"))
        luaScriptFile = right;
    else if (is_similar(left, "FRAMES_PER_SECOND"))
        framesPerSecond = atoi(right);
    else
        return;
}

// parse config
void parseConfig()
{
    FILE *f = NULL;
    char line[1024];
    f = fopen(CONFIG_NAME, "r");
    SDL_assert(f != NULL);
    do_assert(f != NULL, "config file not found!");
    while (!feof(f))
    {
        fgets(line, 1024, f);
        char *txt = line;
        if (!is_contains(txt, "=") || is_starts(txt, "#"))
            continue;
        char *l = strtok(txt, "=");
        char *r = strtok(NULL, "=");
        l = do_trim(l);
        r = do_trim(r);
        parseLine(l, r);
    }
    fclose(f);
}

// parse flag
void parseArgs()
{
    // flag
    flag = SDL_WINDOW_OPENGL;
    if (windowCanResize) flag = flag | SDL_WINDOW_RESIZABLE;
    if (windowNoBorder) flag = flag | SDL_WINDOW_BORDERLESS;
    if (windowIsHidden) flag = flag | SDL_WINDOW_HIDDEN;
    if (windowOnTop) flag = flag | SDL_WINDOW_ALWAYS_ON_TOP;
    if (windowSkipTask) flag = flag | SDL_WINDOW_SKIP_TASKBAR;
    if (is_similar(windowSizeState, "FULL"))
        flag = flag | SDL_WINDOW_FULLSCREEN_DESKTOP;
    else if (is_similar(windowSizeState, "MAX"))
        flag = flag | SDL_WINDOW_MAXIMIZED;
    else if (is_similar(windowSizeState, "MIN"))
        flag = flag | SDL_WINDOW_MINIMIZED;
    // frame
    framesPerSecond = get_min(get_max(framesPerSecond, 0), 60);
    frameTime = framesPerSecond > 0 ? 1000 / framesPerSecond : 0;
}

// main entrance
int main(int argc, char **argv)
{
    // config
    parseConfig();
    // args
    parseArgs();
    // new
    stage = Stage_new();
    bridge = Bridge_new();
    // create
    Stage_create(stage, windowTitle, windowWidth, windowHeight, flag);
    window = stage->window;
    renderer = stage->renderer;
    Bridge_create(bridge);
    // init lua
    Bridge_register(bridge);
    Bridge_run(bridge, luaScriptFile);
    // start
    Stage_start(stage);
    // loop
    while (Stage_running(stage))
    {
        if(framesPerSecond == 0)
        {
            // handle event
            SDL_Event event;
            if (SDL_WaitEvent(&event)) Stage_handle(stage, event);
            //
        } else {
            // frage start
            Stage_before(stage);
            // record time
            uint32_t startTime = SDL_GetTicks();
            // handle event
            SDL_Event event;
            if (SDL_PollEvent(&event)) Stage_handle(stage, event);
            // update state
            Stage_update(stage);
            // render objects
            Stage_render(stage);
            // frame delay
            uint32_t endTime = SDL_GetTicks();
            int32_t costTime = endTime - startTime;
            int32_t leftTime = frameTime - costTime;
            int32_t delayTime = get_max(leftTime, 0);
            SDL_Delay(delayTime);
            // frame end
            Stage_after(stage);
            //
        }
    }
    // exit program
    Stage_release(stage);
    Bridge_release(bridge);
    exit(EXIT_SUCCESS);
}
