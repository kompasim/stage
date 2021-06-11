// http://blog.chinaunix.net/uid-20587912-id-405049.html
// https://blog.csdn.net/leixiaohua1020/article/details/40701203

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

 const   int  WINDOW_WIDTH  =   640 ;
 const   int  WINDOW_HEIGHT  =   480 ;
 const   char *  WINDOW_TITLE  =   " SDL Start " ;

 

 int  main( int  argc,  char   ** argv)

 {
 


    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
        fprintf(stderr, "\nERROR:%s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "demo",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    bool quit = false;
    SDL_Event event;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_MaximizeWindow(window);


    // while(true) printf("");
   SDL_Quit();

}
