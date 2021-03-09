// Trent Julich ~ 03/02/2021

#include "tetris_board.hpp"
#include <iostream>

TetrisBoard::TetrisBoard() {
  rows_ = 20;
  cols_ = 10;
  std::vector<char> empty_row(cols_);
  std::vector<std::vector<char>> all_rows(rows_);
  std::fill(empty_row.begin(), empty_row.end(), '-');
  std::fill(all_rows.begin(), all_rows.end(), empty_row);
  blocks_ = all_rows;
}

TetrisBoard::~TetrisBoard() {

}

void TetrisBoard::ClearRows() {
  std::vector<char> current_row;
  bool should_clear = true;
  for (int i = 0; i < blocks_.size(); i++) {
    current_row = blocks_[i];
    for (int j = 0; j < current_row.size(); j++) {
      if (current_row[j] == '-') {
        should_clear = false;
        break;
      }
    }
    if (should_clear) {
      std::vector<char> empty_row(cols_);
      std::fill(empty_row.begin(), empty_row.end(), '-');
      blocks_.erase(blocks_.begin() + i);
      blocks_.insert(blocks_.begin(), empty_row);
    }
    should_clear = true;
  }
}

char TetrisBoard::GetBlock(int p_row, int p_col) {
  return blocks_[p_row][p_col];
}

int TetrisBoard::get_rows() {
  return rows_;
}

int TetrisBoard::get_cols() {
  return cols_;
}

bool TetrisBoard::IsBlockFilled(int p_row, int p_col) {
  return !(blocks_[p_row][p_col] == '-');
}

void TetrisBoard::SetBlock(int p_row, int p_col, char p_block_type) {
  blocks_[p_row][p_col] = p_block_type;
}

void TetrisBoard::PrintBoard() {
  std::cout << "PRINTING BOARD" << std::endl;
  for(int i = 0; i < blocks_.size(); i++) {
    for(int j = 0; j < blocks_[i].size(); j++) {
      std::cout << blocks_[i][j];
      if (j != blocks_[i].size()-1) {
        std::cout << ",";
      }
    }
    std::cout << std::endl;
  }
}
