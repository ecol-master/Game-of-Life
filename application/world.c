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

int Next(World *world, int x, int y)
{
    int n = Neighbours(world, x, y);
    int alive = world->cells[x][y];
    if (n < 4 & n > 1 & alive)
    {
        return 1;
    }
    if (n == 3 & !alive)
    {
        return 1;
    }
    return 0;
}

int Neighbours(World *world, int x, int y)
{
    int neighs = 0;
    int **newCells = calloc(3 * world->height, sizeof(int *));
    for (int i = 0; i < 3 * world->height; i++)
    {
        newCells[i] = calloc(3 * world->width, sizeof(int *));
    }
    for (int i = 0; i < 3 * world->height; i++)
    {
        for (int j = 0; j < 3 * world->width; j++)
        {
            newCells[i][j] = world->cells[i % world->height][j % world->width];
        }
    }

    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if (i == j & i == 0)
            {
                continue;
            }
            if (newCells[world->height + y + j][world->width + x + i])
            {
                neighs++;
            }
        }
    }
    return neighs;
}

void NextState(World *oldWorld, World *newWorld)
{
    // переберём все клетки, чтобы понять, в каком они состоянии
    for (int i = 0; i < oldWorld->height; i++)
    {
        for (int j = 0; j < oldWorld->width; j++)
        {
            // для каждой клетки получим новое состояние
            newWorld->cells[i][j] = Next(oldWorld, i, j);
        }
    }
}

void PrintWorld(World *world)
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