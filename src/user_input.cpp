#include "user_input.hpp"
#include <iostream>

void handleKeyDown(SDL_Keycode key) {
    switch(key) 
    {
        case SDLK_a:
        case SDLK_LEFT:
            std::cout << "Move left" << std::endl;
            current_game->MoveLeft();
            break;
        case SDLK_d:
        case SDLK_RIGHT:
            std::cout << "Move right" << std::endl;
            current_game->MoveRight();
            break;
        case SDLK_w:
        case SDLK_UP:
            std::cout << "Drop" << std::endl;
            break;
        case SDLK_s:
        case SDLK_DOWN:
            std::cout << "Slow drop" << std::endl;
            current_game->MoveDown();
            break;
    }
}

void handleUserInput(SDL_Event e) 
{
    switch(e.type) 
    {
        case SDL_KEYDOWN:
            handleKeyDown(e.key.keysym.sym);
            break;
    }
}
