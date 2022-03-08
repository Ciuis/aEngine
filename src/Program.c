#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 640
#define CELL_WIDTH 128
#define CELL_HEIGHT 128

typedef enum { false, true } bool;

typedef struct Cell {
    SDL_Surface* image;
} Cell;

typedef struct LVL {
    unsigned w;
    unsigned h;

    Cell*** cells;
} LVL;

// Prototypes
int SDLInit(char* title, unsigned int width, unsigned int height, SDL_Window** window, SDL_Surface** screen_surface);
int SDLDestroy();
int loadIMG(char* path, SDL_Surface** img);
int surfacePlace(unsigned x, unsigned y, SDL_Surface* src, SDL_Surface* screen);
int readLVL(char* path, LVL* level);

// MAIN FUNCTION
int main(void) {
    SDL_Window* window = NULL;
    SDL_Surface* screen_surface = NULL;

    if (SDLInit("AENGINE", SCREEN_WIDTH, SCREEN_HEIGHT, &window, &screen_surface)) {
#ifdef DEBUG
        printf("SDL could not initialized! SDL_ERROR: %s\n", SDL_GetError());
#endif
        goto cleanup;
    }

    SDL_Surface* grass = NULL;
    if (loadIMG("../grass.png", &grass)) {
        goto cleanup;
    }

    SDL_Surface* wall = NULL;
    if (loadIMG("../wall.png", &wall)) {
        goto cleanup;
    }

    if (surfacePlace(CELL_WIDTH, CELL_HEIGHT, grass, screen_surface)) {
        goto cleanup;
    }

    if (surfacePlace(CELL_WIDTH, CELL_HEIGHT, wall, screen_surface)) {
        goto cleanup;
    }

    /* MAIN LOOP */
    SDL_UpdateWindowSurface(window);

    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

cleanup:
    SDLDestroy(&window);

    return 0;
}

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

int SDLDestroy(SDL_Window** window) {
    //Kill window
    SDL_DestroyWindow(*window);
    *window = NULL;
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

int surfacePlace(unsigned x, unsigned y, SDL_Surface* src, SDL_Surface* screen) {
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

int readLVL(char* path, LVL* level) {
    FILE* file = fopen(path, "r");
    unsigned w;
    unsigned h;
    if (fscanf("%u %u", &w, &h) != 2) {
#ifdef DEBUG
        printf("Can't read LVL size.\n");
#endif
        goto error;
    }

    level->w = w;
    level->h = h;
    level->cells = (Cell***)malloc(sizeof(Cell**) * level->w);

    fclose(file);
    return 0;

error:
    fclose(file);

    return 1;
}