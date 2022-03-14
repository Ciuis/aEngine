#include "sdlike.h"
#include "constants.h"

int SDLInit(char* title, unsigned int width, unsigned int height, SDL_Window** window, SDL_Surface** screen_surface) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return 1;
    }

    *window = SDL_CreateWindow(title,
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               width,
                               height,
                               SDL_WINDOW_SHOWN);
    if (*window == NULL) {
        return 2;
    }

    *screen_surface = SDL_GetWindowSurface(*window);
    if (*screen_surface == NULL) {
        return 3;
    }

    return 0;
}

int SDLDestroy(SDL_Window** window, SDL_Surface** screen) {
    //Kill window
    SDL_DestroyWindow(*window);
    *window = NULL;
    SDL_FreeSurface(*screen);
    *screen = NULL;

    //Quit SDL subsystem
    SDL_Quit();

    return 0;
}

int loadIMG(char* path, SDL_Surface** img) {
    if ((*img = IMG_Load(path)) == NULL) {
#ifdef DEBUG
        printf("Image could not load: '%s'. SDL_ERROR: %s\n", path, SDL_GetError());
#endif
        return 1;
    }

    return 0;
}

int surfacePlacePx(unsigned x, unsigned y, SDL_Surface* src, SDL_Surface* screen) {
    SDL_Rect scr_rect = {
            .x = 0, .y = 0,
            .w = CELL_WIDTH, .h = CELL_HEIGHT
    };
    SDL_Rect dst_rect = {
            .x = x, .y = y,
            .w = CELL_WIDTH, .h = CELL_HEIGHT
    };

    if (SDL_BlitSurface(src, &scr_rect, screen, &dst_rect)) {
#ifdef DEBUG
        printf("Can't place a surface. SDL_ERROR: %s\n", SDL_GetError());
#endif
        return 1;
    }

    return 0;
}

int surfacePlacePos(unsigned x, unsigned y, SDL_Surface* src, SDL_Surface* screen) {
    return surfacePlacePx(x * CELL_WIDTH, y * CELL_HEIGHT, src, screen);
}