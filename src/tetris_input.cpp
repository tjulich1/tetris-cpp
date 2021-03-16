#include "tetris_input.hpp"
#include "tetris_events.hpp"
#include <iostream>

TetrisInput::TetrisInput(TetrisGame* game) {
  game_ = game;
}

TetrisInput::~TetrisInput() {
  game_ = 0;
}

bool TetrisInput::HandleInput() {
  bool quit = false;
  while(SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
			quit = true;
		} else if (game_->IsPaused()) {
      // TEMP FIX, move key down check 
      if (e.type == SDL_KEYDOWN) {HandlePaused(e);}
    } else {
      HandleUnpaused(e);
    }
  }
  return quit;
}

void TetrisInput::HandleUnpaused(SDL_Event e) {
  if (e.type == SDL_USEREVENT && e.user.code == DROP) {
    game_->MoveDown();
  }

  if (e.type == SDL_KEYDOWN) {
    switch (e.key.keysym.sym) {
      case SDLK_LEFT:
        game_->MoveLeft();
        break;
      case SDLK_RIGHT:
        game_->MoveRight();
        break;
      case SDLK_x:
      case SDLK_UP:
        game_->RotateClockwise();
        break;
      case SDLK_DOWN:
        game_->MoveDown();
        break;
      case SDLK_SPACE:
        game_->DropPiece();
        break;
      case SDLK_LCTRL:
      case SDLK_RCTRL:
      case SDLK_z:
        game_->RotateCounterClockwise();
        break;
      case SDLK_RSHIFT:
      case SDLK_LSHIFT:
      case SDLK_c:
        std::cout << "Hold piece" << std::endl;
        break;
      case SDLK_ESCAPE:
        game_->TogglePause();
        break;
    }
  }
}

void TetrisInput::HandlePaused(SDL_Event e) {
  if (e.key.keysym.sym == SDLK_ESCAPE) {
    game_->TogglePause();
  }
}