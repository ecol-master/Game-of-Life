#define _CRT_SECURE_NO_WARNINGS
#include "../application/world.c"
#include <time.h>

void waitFor(unsigned int secs)
{
    unsigned int retTime = time(0) + secs;
    while (time(0) < retTime)
        ;
}

int main()
{
    Config config = {10, 10};

    int **cells = GenerateWorldCells(&config);

    World currentWorld = {config.height, config.width, cells};
    World nextWorld = {config.height, config.width, cells};
    while (1 > 0)
    {
        PrintWorld(&currentWorld);
        NextState(&currentWorld, &nextWorld);
        currentWorld = currentWorld;
        waitFor(1);
        printf("\033[H\033[2J");
    }
    return 0;
}