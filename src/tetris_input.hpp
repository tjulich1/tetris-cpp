#include "tetris_game.hpp"
#include <SDL.h>

class TetrisInput {
  public:
    TetrisInput(TetrisGame* game);
    ~TetrisInput();
    bool HandleInput();
  private:
    TetrisGame* game_;
    SDL_Event e;

    void HandleUnpaused(SDL_Event e);
    void HandlePaused(SDL_Event e);
};