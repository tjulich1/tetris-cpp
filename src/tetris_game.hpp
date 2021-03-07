// Trent Julich ~ 03/02/2021

#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include "piece_generator.hpp"
#include "tetris_board.hpp"
#include <SDL.h>

const std::vector<char> kBlockTypes{'z'};
const int kBlockDim = 20;
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
    void RotateClockwise();
    void RotateCounterClockwise();
  private: 
    PieceGenerator generator_;
    TetrisBoard board_;
    TetrisPiece current_piece_;
    SDL_Renderer* renderer_; 

    unsigned int timer_interval_;

    bool IsPieceInBounds(PieceState p_state_to_check, int p_row_transform, int p_col_transform);
    bool CheckCollisions(PieceState p_state_to_check, int p_row_transform, int p_col_transform);
    bool IsLegalMove(int p_state_number, int p_row_transform, int p_col_transform);
    
    void LockPiece();
    void NextPiece();
    bool IsClockwiseClear();
};

#endif