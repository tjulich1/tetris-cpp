// Trent Julich ~ 03/02/2021

#ifndef TETRIS_BOARD_H
#define TETRIS_BOARD_H

#include <vector>

class TetrisBoard {
  public:
    TetrisBoard();
    ~TetrisBoard();
    void PrintBoard();
    bool IsBlockFilled(int p_row, int p_col);
    void SetBlock(int p_row, int p_col, char p_block_type);
    char GetBlock(int p_row, int p_col);
    void ClearRows();
    int get_rows();
    int get_cols();
  private:
    std::vector<std::vector<char>> blocks_;
    int rows_ = 20;
    int cols_ = 10;
};

#endif