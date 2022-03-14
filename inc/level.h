#ifndef _LEVEL_H_
#define _LEVEL_H_
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>

typedef enum { false, true } bool;

typedef struct Cell {
    char* type;
    SDL_Surface* image;
} Cell;

/**
 * Gaming area.
 * Field "cells" in two-dimensional array
 * Cell* [x, x, x, x, x]
 * Cell** x -> [y, y, y, y, y]
 *
 */

typedef struct LVL {
    unsigned int w;
    unsigned int h;
    Cell*** cells;
} LVL;

/**
 * Read text file with cells definition and make level.
 * @param path -- filepath (example: "../filename.tmp")
 * @param level -- reference to level
 * @return
 */
int makeLVL(char* path, LVL* level);

/**
 * Debug function (to check level correctness).
 * @param level -- filepath (example: "../filename.tmp")
 */
void printLVL(LVL* level);


/**
 *
 * @param level -- reference to level
 * @param screen -- reference to screen
 * @return
 */
int placeLVL(LVL* level, SDL_Surface* screen);

#endif // _LEVEL_H_