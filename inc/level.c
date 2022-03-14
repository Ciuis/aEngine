#include "level.h"
#include "sdlike.h"

int makeLVL(char* path, LVL* level) {
    FILE* file = fopen(path, "r");
    printf("File open - done\n");
    unsigned int w;
    unsigned int h;

    if (fscanf(file, "%u %u", &w, &h) != 2) {
#ifdef DEBUG
        printf("Can't read LVL size.\n");
#endif
        goto error;
    }
    printf("Level load == OK\n");

    level->w = w;
    level->h = h;

    SDL_Surface* grass = NULL;
    if (loadIMG("../grass.png", &grass)) {
        goto error;
    }

    SDL_Surface* wall = NULL;
    if (loadIMG("../wall.png", &wall)) {
        goto error;
    }

    level->cells = (Cell***)malloc(sizeof(Cell**) * level->w);

    for (int x = 0; x < level->w; ++x) {
        level->cells[x] = (Cell**) malloc(sizeof(Cell*) * level->h);

        for (int y = 0; y < level->h; ++y) {
            level->cells[x][y] = (Cell*)malloc(sizeof(Cell));

            char cell_type;
            retry:
            cell_type = fgetc(file);

            switch (cell_type) {
                case ' ':
                    level->cells[x][y]->type = "grass";
                    level->cells[x][y]->image = grass;
                    break;
                case '#':
                    level->cells[x][y]->type = "wall";
                    level->cells[x][y]->image = wall;
                    break;
                case EOF:
                    printf("Bad level file\n");
                    goto error;
                default:
                    goto retry;
            }
        }
    }

    if(file) {
        fclose(file);
    } else {
        printf("File open error!\n");
    }

    return 0;

    error:
    fclose(file);

    return 1;
}

void printLVL(LVL* level) {
    for (int x = 0; x < level->w; ++x) {
        for (int y = 0; y < level->h; ++y) {
            //printf("Print cell %u;%u type %s\n", x, y, level->cells[x][y]->type);
            if (strcmp(level->cells[x][y]->type, "grass") == 0) {
                printf(" ");
            } else if (strcmp(level->cells[x][y]->type, "wall") == 0) {
                printf("#");
            } else {
#ifdef DEBUG
                default: printf("Unknown cell type '%s'\n", level->cells[x][y]->type);
#endif
            }
        }
        printf("\n");
    }
}

int placeLVL(LVL* level, SDL_Surface* screen) {
    int success = 0;
    for (int x = 0; x < level->w; ++x) {
        for (int y = 0; y < level->h; ++y) {
            //printf("Print cell %u;%u type %s\n", x, y, level->cells[x][y]->type);
            success |= surfacePlacePos(x, y, level->cells[x][y]->image, screen);
        }
    }

    return success;
}
