#include <iostream>
#include "Game.h"
#include "Renderer_SDL.h"


int main(int argc, char* argv[])
{
    try{
        SDLContext sdlContext(SCREEN_WIDTH, SCREEN_HEIGHT);

        Game game(GRID_WIDTH, GRID_HEIGHT);

        Run(sdlContext, game, FRAME_RATE);

        std::cout << "Game has terminated successfully, score: " << game.GetScore()
            << ", size: " << game.GetSnake().GetSize() << std::endl;
    }
    catch (std::exception const& e) {
        std::cerr << e.what();
    }

    return 0;
}