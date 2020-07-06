//#include "Game.h"
//
//int main(int argc, char* argv[]) {
//    srand(time(NULL));
//    const int frameRate = 5;
//    const int frameDelay = 1000 / frameRate;
//
//    Uint32 frameTime;
//    int frameElapsedTime;
//
//    Game* game = new Game();
//    game->init("Snake game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, G_SIZE, G_SIZE, false);
//    while (game->isRunning()) {
//        frameTime = SDL_GetTicks();
//
//        game->handleEvents();
//        game->update();
//        game->render();
//
//        frameElapsedTime = SDL_GetTicks() - frameTime;
//        if (frameDelay > frameElapsedTime)
//            SDL_Delay(frameDelay - frameElapsedTime);
//    }
//    game->clean();
//    return 0;
//}

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