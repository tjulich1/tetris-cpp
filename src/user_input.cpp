// Trent Julich ~ 03/02/2021

#include "user_input.hpp"
#include <iostream>

void HandleKeyDown(SDL_Keycode key) {
  switch(key) {
    case SDLK_LEFT:
      current_game->MoveLeft();
      break;
    case SDLK_RIGHT:
      current_game->MoveRight();
      break;
    case SDLK_x:
    case SDLK_UP:
      current_game->RotateClockwise();
      break;
    case SDLK_DOWN:
      current_game->MoveDown();
      break;
    case SDLK_SPACE:
      current_game->DropPiece();
      break;
    case SDLK_LCTRL:
    case SDLK_RCTRL:
    case SDLK_z:
      current_game->RotateCounterClockwise();
      break;
    case SDLK_RSHIFT:
    case SDLK_LSHIFT:
    case SDLK_c:
      std::cout << "Hold piece" << std::endl;
      break;
    case SDLK_ESCAPE:
      std::cout << "Pause game" << std::endl;
      current_game->Pause();
      break;
    }
}

void HandleUserInput(SDL_Event e) {
  switch(e.type) {
    case SDL_KEYDOWN:
      HandleKeyDown(e.key.keysym.sym);
      break;
  }
}
