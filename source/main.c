// main

#include "head.h"
#include "tools.c"
#include "window.c"
#include "render.c"
#include "others.c"
#include "bridge.c"
#include "test.c"
#include "stage.c"

// config
const char *CONFIG_NAME = "config.txt";

// args
char *windowTitle = "Stage";
int windowWidth = 480;
int windowHeight = 480;
int windowFrameCount = 0;
bool windowCanResize = false;
bool windowNoBorder = false;
bool windowIsHidden = false;
bool windowOnTop = false;
bool windowSkipTask = false;
char *windowSizeState = "EMPTY";
char *mainScriptFile = "stage.lua";

uint32_t frameTime = 0;
Uint32 flag = 0;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
bool automatic = false;

// parse line
void parseLine(char *left, char *right)
{
    if (is_similar(left, "WINDOW_TITLE"))
        windowTitle = right;
    else if (is_similar(left, "WINDOW_WIDTH"))
        windowWidth = atoi(right);
    else if (is_similar(left, "WINDOW_HEIGHT"))
        windowHeight = atoi(right);
    else if (is_similar(left, "WINDOW_FRAME_COUNT"))
        windowFrameCount = atoi(right);
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
    else if (is_similar(left, "MAIN_SCRIPT_FILE"))
        mainScriptFile = right;
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
    windowFrameCount = get_max(windowFrameCount, 0);
    windowFrameCount = get_min(windowFrameCount, 60);
    frameTime = windowFrameCount > 0 ? 1000 / windowFrameCount : 0;
}

// main entrance
int main(int argc, char **argv)
{
    // config
    parseConfig();
    // args
    parseArgs();
    // new
    Stage *stage = Stage_new(windowTitle, windowWidth, windowHeight, flag);
    window = stage->window;
    renderer = stage->renderer;
    // create
    Stage_create(stage);
    // type
    bool isWait = frameTime == 0;
    // loop
    while (Stage_running(stage))
    {
        uint32_t startTime = SDL_GetTicks();
        // handle event
        Stage_handle(stage, isWait);
        // update state
        Stage_update(stage);
        // render objects
        Stage_render(stage);
        // frame delay
        uint32_t endTime = SDL_GetTicks();
        int32_t costTime = endTime - startTime;
        int32_t leftTime = frameTime - costTime;
        SDL_Delay(get_max(leftTime, 0));
    }
    // exit program
    Stage_release(stage);
    exit(EXIT_SUCCESS);
}
