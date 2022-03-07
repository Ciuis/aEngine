#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int SDLInit(char* title, unsigned int width, unsigned int height, SDL_Window** window);
int SDLDestroy();
int loadIMG(char* path, SDL_Window** window);

int main(void) {
    SDL_Window* window = NULL;

    if (SDLInit("AENGINE", SCREEN_WIDTH, SCREEN_HEIGHT, &window)) {
#ifdef DEBUG
        printf("SDL could not initialized! SDL_ERROR: %s\n", SDL_GetError());
#endif
    }

    /* MAIN LOOP */
    SDL_Surface* img = NULL;

    SDL_Delay(2000);
    SDLDestroy(&window);

    return 0;
}

int SDLInit(char* title, unsigned int width, unsigned int height, SDL_Window** window) {
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

int loadIMG(char* path, SDL_Window** window) {
    IMG_Load()
}
