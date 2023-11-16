#define _CRT_SECURE_NO_WARNINGS
#include "../worlds-map/worlds.c"
#include <time.h>
#include <Windows.h>

void waitFor(unsigned int secs)
{
    unsigned int retTime = time(0) + secs;
    while (time(0) < retTime)
        ;
}

int main()
{
    // Значения h: 20, w:20 - для поля
    Config config = {20, 20};

    int **cells = GenerateWorldCells(&config);
    World currentWorld = {config.height, config.width, cells};
    SetInitialState(&currentWorld);

    int **cells2 = GenerateWorldCells(&config);
    World nextWorld = {config.height, config.width, cells2};

    while (1 > 0)
    {
        PrintWorld(&currentWorld);
        int **newCells = NextState(&currentWorld, &nextWorld);
        currentWorld.cells = newCells;

        waitFor(1);
        printf("\033[H\033[2J");
    }
    return 0;
}