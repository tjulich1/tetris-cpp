// Trent Julich ~ 03/02/2021

#include "user_input.hpp"
#include <iostream>

void HandleKeyDown(SDL_Keycode key) {
    switch(key) 
    {
        // case SDLK_a:
        case SDLK_LEFT:
            std::cout << "Move left" << std::endl;
            current_game->MoveLeft();
            break;
        // case SDLK_d:
        case SDLK_RIGHT:
            std::cout << "Move right" << std::endl;
            current_game->MoveRight();
            break;
        case SDLK_x:
        case SDLK_UP:
            std::cout << "Rotate Clockwise" << std::endl;
            current_game->RotateClockwise();
            break;
        // case SDLK_s:
        case SDLK_DOWN:
            std::cout << "Slow drop" << std::endl;
            current_game->MoveDown();
            break;
        case SDLK_SPACE:
            std::cout << "Hard Drop" << std::endl;
            current_game->DropPiece();
            break;
        case SDLK_LCTRL:
        case SDLK_RCTRL:
        case SDLK_z:
            std::cout << "Rotate Counter-Clockwise" << std::endl;
            current_game->RotateCounterClockwise();
            break;
        case SDLK_RSHIFT:
        case SDLK_LSHIFT:
        case SDLK_c:
            std::cout << "Hold piece" << std::endl;
            break;
    }
}

void HandleUserInput(SDL_Event e) 
{
    switch(e.type) 
    {
        case SDL_KEYDOWN:
            HandleKeyDown(e.key.keysym.sym);
            break;
    }
}
