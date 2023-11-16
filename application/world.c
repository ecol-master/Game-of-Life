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
    int alive = world->cells[y][x];
    if (n < 4 && n > 1 && alive == 1)
    {
        return 1;
    }
    if (n == 3 && alive == 0)
    {
        return 1;
    }
    return 0;
}

int Neighbours(World *world, int x, int y)
{
    int neightbours = 0;
    for (int i = y - 1; i < y + 2; i++)
    {
        for (int j = x - 1; j < x + 2; j++)
        {
            if (i == y && j == x)
            {
                continue;
            }
            if (i < 0 || j < 0 || i >= world->height || j >= world->width)
            {
                continue;
            }
            if (world->cells[i][j] == 1)
            {
                neightbours++;
            }
        }
    }
    return neightbours;
}

int **NextState(World *oldWorld, World *newWorld)
{
    int **newCells = calloc(oldWorld->height, sizeof(int *));
    for (int i = 0; i < oldWorld->height; i++)
    {
        newCells[i] = calloc(oldWorld->width, sizeof(int));
    }

    for (int y = 0; y < oldWorld->height; y++)
    {
        for (int x = 0; x < oldWorld->width; x++)
        {
            // для каждой клетки получим новое состояние
            newCells[y][x] = Next(oldWorld, x, y);
        }
    }
    return newCells;
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
