// stage

#include "head.h"

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool running;
} Stage;

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

void Stage_start(Stage *this)
{
    this->running = true;
    // TODO: notify lua
    testCode();
}

void Stage_stop(Stage *this)
{
    // TODO: notify lua
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
    // TODO: notify lua
}

void Stage_handle(Stage *this ,SDL_Event event)
{
    if (event.type == SDL_QUIT)
    {
        Stage_stop(this);
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
            // do_message("f1 down"); // SDL_KeyCode
            testF1();
        }
    }
    else if (event.type == SDL_KEYUP) // Key released
    {
        if (event.key.keysym.sym == SDLK_F2)
        {
            // do_message("f1 up"); // SDL_KeyCode
            testF2();
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
    // TODO: notify lua
}

void Stage_update(Stage *this)
{
    // TODO: notify lua
}

void Stage_render(Stage *this)
{
    // TODO: notify lua
    printf("[%d]\n", getTick());
}

void Stage_after(Stage *this)
{
    // TODO: notify lua
}
