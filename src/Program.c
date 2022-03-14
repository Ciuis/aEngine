#include "../inc/sdlike.h"
#include "../inc/level.h"

// MAIN FUNCTION
int main(void) {
    SDL_Window* window = NULL;
    SDL_Surface* screen_surface = NULL;

    if (SDLInit("AENGINE", 640, 640, &window, &screen_surface)) {
#ifdef DEBUG
        printf("SDL could not initialized! SDL_ERROR: %s\n", SDL_GetError());
#endif
        goto cleanup;
    }

    LVL level;
    printf("Level creation - done\n");
    makeLVL("../level0.txt", &level);
    //perror("Error: ");
    printf("Level reading - done\n");
    //perror("ERROR: ");
    printLVL(&level);

    /* MAIN LOOP */
    placeLVL(&level, screen_surface);
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
    SDLDestroy(&window, &screen_surface);

    return 0;
}

