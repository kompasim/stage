// stage

// http://blog.chinaunix.net/uid-20587912-id-405049.html
// https://blog.csdn.net/leixiaohua1020/article/details/40701203

#include "tools.c"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "render.c"

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
SDL_Renderer *renderer = NULL;
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
    SDL_DestroyRenderer(renderer);
    SDL_FreeSurface(surface);
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
        if (event.key.keysym.sym == SDLK_F2)
        {
            message("f1 up"); // SDL_KeyCode
        }
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN) // Mouse button pressed
    {
        // printf("\nSDL_MOUSEBUTTONDOWN: key:[%d]", event.button.button); // left 1, middle 2, right 3
    }
    else if (event.type == SDL_MOUSEBUTTONUP) // Mouse button released
    {
        // printf("\nSDL_MOUSEBUTTONUP: key:[%d]", event.button.button); // left 1, middle 2, right 3
    }
    else if (event.type == SDL_MOUSEMOTION) // Mouse moved
    {
        // printf("\nSDL_MOUSEMOTION: x:[%d] y:[%d]", event.button.x, event.button.y);
    }
    else if (event.type == SDL_MOUSEWHEEL) // Mouse wheel motion
    {
        // printf("\nSDL_MOUSEWHEEL: wheel:[%d]", event.wheel.y); // forward 1, backward -1
    }
}

// -------------------------------------------------------------------------------------------------------------------------------------------

uint32_t getTick()
{
    return SDL_GetTicks();
}

void setAuto(bool isAuto)
{
    automatic = isAuto;
}

void update()
{
    SDL_UpdateWindowSurface(window);
}

void show()
{
    SDL_ShowWindow(window);
}

void hide()
{
    SDL_HideWindow(window);
}

void maximaze()
{
    SDL_MaximizeWindow(window);
}

void minimaze()
{
    SDL_MinimizeWindow(window);
}

void setTitle(char *title)
{
    SDL_SetWindowTitle(window, title);
}

const char *getTitle()
{
    return SDL_GetWindowTitle(window);
}

void setPosition(int x, int y)
{
    SDL_SetWindowPosition(window, x, y);
}

void getPosition()
{
    int x;
    int y;
    SDL_GetWindowPosition(window, &x, &y);
}

void setSize(int w, int h)
{
    SDL_SetWindowSize(window, w, h);
}

void getSize()
{
    int w;
    int h;
    SDL_GetWindowSize(window, &w, &h);
}

void setFullscreen(bool isFullscreen)
{
    SDL_SetWindowFullscreen(window, isFullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0); 
}

void showCursor(bool isShow)
{
    SDL_ShowCursor(isShow ? 1 : 0);
}

void setIcon(char *path)
{
    Uint16 pixels[16*16] = {  // ...or with raw pixel data:
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
        0x0fff, 0x0aab, 0x0789, 0x0bcc, 0x0eee, 0x09aa, 0x099a, 0x0ddd,
        0x0fff, 0x0eee, 0x0899, 0x0fff, 0x0fff, 0x1fff, 0x0dde, 0x0dee,
        0x0fff, 0xabbc, 0xf779, 0x8cdd, 0x3fff, 0x9bbc, 0xaaab, 0x6fff,
        0x0fff, 0x3fff, 0xbaab, 0x0fff, 0x0fff, 0x6689, 0x6fff, 0x0dee,
        0xe678, 0xf134, 0x8abb, 0xf235, 0xf678, 0xf013, 0xf568, 0xf001,
        0xd889, 0x7abc, 0xf001, 0x0fff, 0x0fff, 0x0bcc, 0x9124, 0x5fff,
        0xf124, 0xf356, 0x3eee, 0x0fff, 0x7bbc, 0xf124, 0x0789, 0x2fff,
        0xf002, 0xd789, 0xf024, 0x0fff, 0x0fff, 0x0002, 0x0134, 0xd79a,
        0x1fff, 0xf023, 0xf000, 0xf124, 0xc99a, 0xf024, 0x0567, 0x0fff,
        0xf002, 0xe678, 0xf013, 0x0fff, 0x0ddd, 0x0fff, 0x0fff, 0xb689,
        0x8abb, 0x0fff, 0x0fff, 0xf001, 0xf235, 0xf013, 0x0fff, 0xd789,
        0xf002, 0x9899, 0xf001, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0xe789,
        0xf023, 0xf000, 0xf001, 0xe456, 0x8bcc, 0xf013, 0xf002, 0xf012,
        0x1767, 0x5aaa, 0xf013, 0xf001, 0xf000, 0x0fff, 0x7fff, 0xf124,
        0x0fff, 0x089a, 0x0578, 0x0fff, 0x089a, 0x0013, 0x0245, 0x0eff,
        0x0223, 0x0dde, 0x0135, 0x0789, 0x0ddd, 0xbbbc, 0xf346, 0x0467,
        0x0fff, 0x4eee, 0x3ddd, 0x0edd, 0x0dee, 0x0fff, 0x0fff, 0x0dee,
        0x0def, 0x08ab, 0x0fff, 0x7fff, 0xfabc, 0xf356, 0x0457, 0x0467,
        0x0fff, 0x0bcd, 0x4bde, 0x9bcc, 0x8dee, 0x8eff, 0x8fff, 0x9fff,
        0xadee, 0xeccd, 0xf689, 0xc357, 0x2356, 0x0356, 0x0467, 0x0467,
        0x0fff, 0x0ccd, 0x0bdd, 0x0cdd, 0x0aaa, 0x2234, 0x4135, 0x4346,
        0x5356, 0x2246, 0x0346, 0x0356, 0x0467, 0x0356, 0x0467, 0x0467,
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff
    };
    SDL_Surface *icon = SDL_CreateRGBSurfaceFrom(pixels,16,16,16,16*2,0x0f00,0x00f0,0x000f,0xf000);
    // SDL_Surface *icon = IMG_Load(path);
    SDL_SetWindowIcon(window, icon);
}

void getInfo()
{
    int windowW, windowH;
    SDL_GetWindowSize(window, &windowW, &windowH);
    SDL_Rect portRect;
    SDL_RenderGetViewport(renderer, &portRect);
    SDL_Rect clipRect;
    SDL_RenderGetClipRect(renderer, &clipRect);
    float scaleX, scaleY;
    SDL_RenderGetScale(renderer, &scaleX, &scaleY);
}

// -------------------------------------------------------------------------------------------------------------------------------------------

// main entrance
int main(int argc, char **argv)
{
    // config
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
    // init
    assert(TTF_Init() == 0, "ttf init failed!");
    assert(SDL_Init(SDL_INIT_EVERYTHING) == 0, "sdl init failed!");
    // window
    window = SDL_CreateWindow(
        windowTitle,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        flag
    );
    // icon
    setIcon("");
    // initialize
    surface = SDL_GetWindowSurface(window);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    setAuto(true);
    // test
    renderTest();
    // frame time
    windowFrameCount = get_max(windowFrameCount, 0);
    windowFrameCount = get_min(windowFrameCount, 60);
    uint32_t frameTime = windowFrameCount > 0 ? 1000 / windowFrameCount : 0;
    // loop
    while (true)
    {
        uint32_t startTime = SDL_GetTicks();
        SDL_Event event;
        bool isEvent = false;
        // wait event
        if (frameTime == 0)
            isEvent = SDL_WaitEvent(&event);
        else
            isEvent = SDL_PollEvent(&event);
        // handle event
        if (isEvent)  handleEvent(event);
        // frame delay
        uint32_t endTime = SDL_GetTicks();
        int32_t costTime = endTime - startTime;
        int32_t leftTime = frameTime - costTime;
        SDL_Delay(get_max(leftTime, 0));
    }
    // exit program
    exitMain();
}
