#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include "piece_generator.hpp"
#include "tetris_board.hpp"
#include <vector>
#include <SDL.h>

const std::vector<char> kBlockTypes{'z'};
const int kBlockDim = 10;
const static int ROWS = 20;
const static int COLS = 10;

class TetrisGame {
  public:
    TetrisGame(SDL_Renderer* p_renderer);
    ~TetrisGame();
    void Render();
    void MoveLeft();
    void MoveRight();
    void MoveDown();
  private: 
    PieceGenerator generator_;
    TetrisBoard board_;
    TetrisPiece current_piece_;
    SDL_Renderer* renderer_;
};

#endif