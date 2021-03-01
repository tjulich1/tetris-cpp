#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <SDL.h>
#include "tetris_game.hpp"

extern TetrisGame* current_game;

void handleKeyDown(SDL_Event e);

void handleUserInput(SDL_Event e);

#endif