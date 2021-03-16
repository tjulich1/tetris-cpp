// Trent Julich ~ 03/02/2021

#include "tetris_board.hpp"
#include <iostream>

TetrisBoard::TetrisBoard(int p_x_offset, int p_y_offset, int p_block_dim) {
  rows_ = 20;
  cols_ = 10;
  x_offset_ = p_x_offset;
  y_offset_ = p_y_offset;
  block_dim_ = p_block_dim;
  std::vector<char> empty_row(cols_);
  std::vector<std::vector<char>> all_rows(rows_);
  std::fill(empty_row.begin(), empty_row.end(), '-');
  std::fill(all_rows.begin(), all_rows.end(), empty_row);
  blocks_ = all_rows;
}

TetrisBoard::~TetrisBoard() {

}

void TetrisBoard::LockPiece(TetrisPiece p_piece) {
  std::vector<Block> blocks = p_piece.get_current_state().blocks;
  for (int i = 0; i < blocks.size(); i++) {
    int row = p_piece.get_row() + blocks[i].y;
    int col = p_piece.get_col() + blocks[i].x;
    if (row >= 0) {
      blocks_[row][col] = blocks[i].block_code;
    }
  }
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
  return (!(p_row < 0 || p_col < 0) 
    && !(blocks_[p_row][p_col] == '-'));
}

void TetrisBoard::SetBlock(int p_row, int p_col, char p_block_type) {
  if (p_row >= 0 && p_col >= 0) {
    blocks_[p_row][p_col] = p_block_type; 
  }
}

void TetrisBoard::Render(SDL_Renderer* p_renderer, std::map<char, SDL_Color>* p_colors) {
  
  // Draw the perimeter of the board
  SDL_Rect rect{
    x_offset_ - 1, 
    y_offset_ - 1, 
    block_dim_*cols_ + 2,
    block_dim_*rows_ + 2
  };
  SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, 255);
  SDL_RenderDrawRect(p_renderer, &rect);

  // Iterate through each row
  for (int i = 0; i < blocks_.size(); i++) {
    std::vector<char> current_row = blocks_[i];
    // Iterate through each block 
    for (int j = 0; j < current_row.size(); j++) {
      // Check if block is actually filled
      if (current_row[j] != '-') {
        SDL_Color color = p_colors->find(current_row[j])->second;
        SDL_SetRenderDrawColor(p_renderer, color.r, color.g, color.b, 255);
        rect = {
          x_offset_ + j*block_dim_,
          y_offset_ + i*block_dim_,
          block_dim_,
          block_dim_
        };
        SDL_RenderFillRect(p_renderer, &rect);
      }
    }
  }

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
