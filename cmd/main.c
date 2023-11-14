#include "../application/world.c"

int main(){
    Config config = {10, 10};

    int** cells = GenerateWorldCells(&config);

    World world = {config.height, config.width, cells};
    PrintCells(&world);
    return 0;
}