






#include "Game.h"

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

int main()
{
    Game game(SCREEN_WIDTH, SCREEN_HEIGHT);
    game.Init();
    game.Run();
    game.ShutDown();
    return 0;
}
