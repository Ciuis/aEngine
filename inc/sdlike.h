#ifndef _SDLIKE_H_
#define _SDLIKE_H_
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>

/**
 * SDL Window and surface initialization
 * @param title -- window title
 * @param width -- window width
 * @param height -- window height
 * @param window -- window reference
 * @param screen_surface -- surface reference
 * @return
 */
int SDLInit(char* title, unsigned int width, unsigned int height, SDL_Window** window, SDL_Surface** screen_surface);

/**
 * Destructor for SDL window and surface
 * @param window -- window reference
 * @param screen -- surface reference
 * @return
 */
int SDLDestroy(SDL_Window** window, SDL_Surface** screen);

/**
 * Load surface from file
 * @param path -- filepath (example: "../filename.tmp")
 * @param img -- image name reference
 * @return
 */
int loadIMG(char* path, SDL_Surface** img);

/**
 * Copy image data to screen surface
 * @param x -- screen pos X in px
 * @param y -- screen pos Y in px
 * @param src - source image
 * @param screen -- screen surface
 * @return
 */
int surfacePlacePx(unsigned x, unsigned y, SDL_Surface* src, SDL_Surface* screen);

/**
 * Copy image data to screen surface
 * @param x -- screen pos in Cells
 * @param y -- screen pos in Cells
 * @param src - source image
 * @param screen -- screen surface
 * @return
 */
int surfacePlacePos(unsigned x, unsigned y, SDL_Surface* src, SDL_Surface* screen);

#endif // _SDLIKE_H_