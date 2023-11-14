#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "config.c"

typedef struct World World;

struct World
{
    int width;
    int height;
    int **cells;
};

int **GenerateWorldCells(Config *config)
{
    // create cell
    int **cells = calloc(config->height, sizeof(int *));
    for (int i = 0; i < config->height; i++)
    {
        cells[i] = calloc(config->width, sizeof(int));
    }

    srand(time(0));
    // generate cells initial state
    for (int i = 0; i < config->height; i++)
    {
        for (int j = 0; j < config->width; j++)
        {
            cells[i][j] = rand() % 2;
        }
    }
    return cells;
}

void PrintCells(World *world)
{
    for (int i = 0; i < world->height; i++)
    {
        for (int j = 0; j < world->width; j++)
        {
            if (world->cells[i][j] == 0)
            {
                printf("%s", "\xF0\x9F\x9F\xAB");
            }
            else
            {
                printf("%s", "\xF0\x9F\x9F\xA9");
            }
        }
        printf("\n");
    }
}