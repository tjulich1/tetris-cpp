// Trent Julich ~ 03/02/2021

#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <SDL.h>
#include "tetris_game.hpp"

extern TetrisGame* current_game;

void HandleKeyDown(SDL_Event e);

void HandleUserInput(SDL_Event e);

#endif