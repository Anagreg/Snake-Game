#pragma once

#include<SDL.h>
#include<iostream>
#include <string>
#include "Game.h"

struct SDLContext
{
    std::size_t window_width;
    std::size_t window_height;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;


    SDLContext(std::size_t window_width, std::size_t window_height);
    ~SDLContext();
};

void EventHandler(SDLContext&, Game& game);

void Render(SDLContext& context, Game const& game);

void UpdateWindowTitle(SDLContext& context, Game const& game);

void Run(SDLContext& context, Game& game, int frame_rate);
