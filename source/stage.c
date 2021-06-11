// stage

// http://blog.chinaunix.net/uid-20587912-id-405049.html
// https://blog.csdn.net/leixiaohua1020/article/details/40701203

#include "tools.c"
#include <SDL2/SDL.h>

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

// sdl
SDL_Window *window = NULL;
SDL_Surface *surface = NULL;
bool automatic = false;

// set args
void getArgs(char *left, char *right)
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
    else if (is_similar(left, "WINDOW_SIZE_STATE"))
        windowSizeState = right;
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
    assert(f != NULL, "config file not found!");
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
        getArgs(l, r);
    }
    fclose(f);
}

void exitMain()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(EXIT_SUCCESS);
}

void handleEvent(SDL_Event event)
{
    if (event.type == SDL_QUIT)
    {
        exitMain();
    }
    else if (event.type == SDL_SYSWMEVENT) // System specific event
    {
        printf("\nSDL_SYSWMEVENT");
    }
    else if (event.type == SDL_WINDOWEVENT) // Window state change
    {
        // printf("\nSDL_WINDOWEVENT");
    }
    else if (event.type == SDL_DISPLAYEVENT) //  Display state change
    {
        printf("\nSDL_DISPLAYEVENT");
    }
    else if (event.type == SDL_DROPFILE) // The system requests a file open
    {
        // printf("\nSDL_DROPFILE");
    }
    else if (event.type == SDL_CLIPBOARDUPDATE) // The clipboard changed
    {
        // printf("\nSDL_CLIPBOARDUPDATE");
    }
    else if (event.type == SDL_KEYDOWN) // Key pressed
    {
        if (event.key.keysym.sym == SDLK_F1)
        {
            message("f1 down"); // SDL_KeyCode
        }
    }
    else if (event.type == SDL_KEYUP) // Key released
    {
        if (event.key.keysym.sym == SDLK_F1)
        {
            message("f1 up"); // SDL_KeyCode
        }
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN) // Mouse button pressed
    {
        // printf("\nSDL_MOUSEBUTTONDOWN");
    }
    else if (event.type == SDL_MOUSEBUTTONUP) // Mouse button released
    {
        // printf("\nSDL_MOUSEBUTTONUP");
    }
    else if (event.type == SDL_MOUSEMOTION) // Mouse moved
    {
        // printf("\nSDL_MOUSEMOTION");
    }
    else if (event.type == SDL_MOUSEWHEEL) // Mouse wheel motion
    {
        // printf("\nSDL_MOUSEWHEEL");
    }
}

void setAuto(bool isAuto)
{
    automatic = isAuto;
}

void updateStage()
{
    SDL_UpdateWindowSurface(window);
}

void fillRect(int x, int y, int w, int h, int r, int g, int b, int a)
{
    SDL_Rect rect = {x, y, w, h};
    SDL_FillRect(surface, &rect, SDL_MapRGBA(surface->format, r, g, b, a));
    if (!automatic)
        return;
    updateStage();
}

// main entrance
int main(int argc, char **argv)
{
    // config
    assert(SDL_Init(SDL_INIT_EVERYTHING) == 0, "sdl init failed!");
    parseConfig();
    // flag
    Uint32 flag = SDL_WINDOW_OPENGL;
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
    // window
    window = SDL_CreateWindow(
        windowTitle,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        flag
    );
    // surface
    surface = SDL_GetWindowSurface(window);
    setAuto(true);
    // test
    fillRect(0, 0, windowWidth, windowHeight, 0, 100, 0, 255);
    fillRect(50, 50, 100, 100, 100, 50, 100, 255);
    //
    // SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    //
    //
    // SDL_Rect rect = {75, 75, 100, 100};
    // SDL_MaximizeWindow(window);
    // SDL_Delay(500);
    //

    // loop
    int waitTime = 0;
    windowFrameCount = get_max(windowFrameCount, 0);
    windowFrameCount = get_min(windowFrameCount, 60);
    if (windowFrameCount > 0)
    {
        waitTime = 1000 / windowFrameCount;
    }
    while (true)
    {
        SDL_Event event;
        bool isEvent = false;
        if (waitTime == 0)
            isEvent = SDL_WaitEvent(&event);
        else
            isEvent = SDL_PollEvent(&event);
        if (isEvent)
        {
            handleEvent(event);
        }
        SDL_Delay(waitTime);
    }
    exitMain();
}
