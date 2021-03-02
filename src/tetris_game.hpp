// Trent Julich ~ 03/02/2021

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

unsigned int Tick(unsigned int p_interval, void* p);

class TetrisGame {
  public:
    TetrisGame(SDL_Renderer* p_renderer);
    void StartGame();
    void Render();
    void MoveLeft();
    void MoveRight();
    void MoveDown();
  private: 
    PieceGenerator generator_;
    TetrisBoard board_;
    TetrisPiece current_piece_;
    SDL_Renderer* renderer_; 

    unsigned int timer_interval_;
    bool IsUnderPieceClear();
    void LockPiece();
    void NextPiece();
};

#endif