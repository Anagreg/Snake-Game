#include"Renderer_SDL.h"


SDLContext::SDLContext(std::size_t window_width, std::size_t window_height) : window_width(window_width), window_height(window_height)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        throw std::runtime_error("SDL could not initialize!");
    }

    // Create Window
    window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        window_width, window_height, SDL_WINDOW_SHOWN);
    if (!window)
    {
        throw std::runtime_error("Window could not be created!");
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        throw std::runtime_error("Renderer could not be created!");
    }
}

SDLContext::~SDLContext()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void EventHandler(SDLContext&, Game& game)
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            game.running = false;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                game.running = false;
                break;
            case SDLK_UP:
                if (game.GetSnake().last_dir != Direction::down || game.GetSnake().GetSize() == 1)
                    game.GetSnake().dir = Direction::up;
                break;

            case SDLK_DOWN:
                if (game.GetSnake().last_dir != Direction::up || game.GetSnake().GetSize() == 1)
                    game.GetSnake().dir = Direction::down;
                break;

            case SDLK_LEFT:
                if (game.GetSnake().last_dir != Direction::right || game.GetSnake().GetSize() == 1)
                    game.GetSnake().dir = Direction::left;
                break;

            case SDLK_RIGHT:
                if (game.GetSnake().last_dir != Direction::left || game.GetSnake().GetSize() == 1)
                    game.GetSnake().dir = Direction::right;
                break;
            }
        }
    }
}

void Render(SDLContext& context, Game const& game)
{
   
        SDL_Rect block;
        block.w = SCREEN_WIDTH / GRID_WIDTH;
        block.h = SCREEN_WIDTH / GRID_HEIGHT;

        // Clear screen
        SDL_SetRenderDrawColor(context.renderer, 0x1E, 0x1E, 0x1E, 0xFF);
        SDL_RenderClear(context.renderer);

        // Render food
        SDL_SetRenderDrawColor(context.renderer, 0x7F, 0xFF, 0x00, 0xFF);
        block.x = game.GetApple().position.x * block.w;
        block.y = game.GetApple().position.y * block.h;
        SDL_RenderFillRect(context.renderer, &block);

        // Render snake's body
        SDL_SetRenderDrawColor(context.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        for (const Point_2D< std::size_t>& point : game.GetSnake().body)
        {
            block.x = point.x * block.w;
            block.y = point.y * block.h;
            SDL_RenderFillRect(context.renderer, &block);
        }

        // Render snake's head
        block.x = game.GetSnake().head.x * block.w;
        block.y = game.GetSnake().head.y * block.h;
        if (game.GetSnake().isAlive) SDL_SetRenderDrawColor(context.renderer, 0x7F, 0xB3, 0xD5, 0xFF);
        else       SDL_SetRenderDrawColor(context.renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(context.renderer, &block);

        // Update Screen
        SDL_RenderPresent(context.renderer);
   
}

void UpdateWindowTitle(SDLContext& context, Game const& game)
{
   
    if (!game.GetSnake().isAlive) {
        std::string title = "You're dead! Game over";
        SDL_SetWindowTitle(context.window, title.c_str());
    } 
    else {
        std::string title = "Snakle++ Score: " + std::to_string(game.GetScore());
        SDL_SetWindowTitle(context.window, title.c_str());
    }

}

void Run(SDLContext& context, Game& game, int frame_rate)
{
    Uint32 before, second = SDL_GetTicks(), after;
    int frame_time;

    while (true)
    {
        before = SDL_GetTicks();

        game.running = true;
        EventHandler(context, game);

        if (!game.running)
            break;

        game.Update();

        Render(context, game);

        after = SDL_GetTicks();
        frame_time = after - before;

        if (after - second >= 1000)
        {
            UpdateWindowTitle(context, game);

            second = after;
        }

        if (frame_rate > frame_time)
        {
            SDL_Delay(frame_rate - frame_time);
        }
    }
}