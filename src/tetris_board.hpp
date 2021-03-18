// Trent Julich ~ 03/02/2021

#ifndef TETRIS_BOARD_H
#define TETRIS_BOARD_H

#include <vector>
#include <map>
#include "tetris_piece.hpp"
#include <SDL.h>

class TetrisBoard {
  public:
    TetrisBoard(int p_x_offset = 0, int p_y_offset = 0, int p_block_dim = 10);
    bool IsBlockFilled(int p_row, int p_col);
    char GetBlock(int p_row, int p_col);
    void ClearRows();
    int get_rows();
    int get_cols();
    void LockPiece(TetrisPiece p_piece);
    void Render(SDL_Renderer* p_renderer, std::map<char, SDL_Color>* p_colors);
  private:
    std::vector<std::vector<char>> blocks_;
    int rows_;
    int cols_;
    int x_offset_;
    int y_offset_;
    int block_dim_;
};

#endif