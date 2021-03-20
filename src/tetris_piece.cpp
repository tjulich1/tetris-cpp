// Trent Julich ~ 03/02/2021

#include "tetris_piece.hpp"
#include <iostream>

TetrisPiece::TetrisPiece(const std::vector<PieceState> p_states, char p_piece_type) 
  : current_state_(0), states_(p_states), col_(default_col_), row_(-p_states[0].height), 
    piece_type_(p_piece_type), x_offset_(0), y_offset_(0)  { }

TetrisPiece::TetrisPiece() : current_state_(-1), row_(0), col_(0), piece_type_('-') { }

PieceState TetrisPiece::get_current_state() {
  if (current_state_ != -1) {
    return states_[current_state_];
  } else {
    return states_[0];
  }
}

PieceState TetrisPiece::get_clockwise_state() {
  return states_[(current_state_+1)%states_.size()];
}

PieceState TetrisPiece::get_counter_clockwise_state() {
  return states_[(current_state_-1)%states_.size()];
}

void TetrisPiece::Right() {
  col_+=1;
}

void TetrisPiece::Left() {
  col_-=1;
}

void TetrisPiece::Down() {
  row_+=1;
}

void TetrisPiece::Clockwise() {
  current_state_ = (current_state_ + 1) % states_.size();
}

void TetrisPiece::CounterClockwise() {
  if (current_state_ == 0) {
    current_state_ = states_.size() - 1;
  } else {
    current_state_--;
  }
}

void TetrisPiece::Render(SDL_Renderer* p_renderer, std::map<char, SDL_Color>* p_colors) {
  SDL_Color piece_color = p_colors->find(piece_type_)->second;
  SDL_SetRenderDrawColor(p_renderer, piece_color.r, piece_color.g, piece_color.b, 255);
  PieceState cur_state = states_[current_state_];

  // Draw each of the blocks of the current piece.
  for (int i = 0; i < cur_state.blocks.size(); i++) {
    Block current_block = cur_state.blocks[i];
    SDL_Rect rect = {
      x_offset_ + (col_+current_block.x)*block_dim_,
      y_offset_ + (row_+current_block.y)*block_dim_,
      block_dim_,
      block_dim_
    };
    SDL_RenderFillRect(p_renderer, &rect);
  }
}

void TetrisPiece::SetXOffset(int p_x_offset) {
  x_offset_ = p_x_offset;
}

void TetrisPiece::SetYOffset(int p_y_offset) {
  y_offset_ = p_y_offset;
}

void TetrisPiece::SetCol(int p_col) {
  col_ = p_col;
}

void TetrisPiece::SetRow(int p_row) {
  row_ = p_row;
}

void TetrisPiece::SetBlockDim(int p_block_dim) {
  block_dim_ = p_block_dim;
}

int TetrisPiece::get_col() {
  return col_;
}

int TetrisPiece::get_row() {
  return row_;
}

char TetrisPiece::get_type() {
  return piece_type_;
}

void TetrisPiece::ResetPosition() {
  row_ = -states_[current_state_].height;
  col_ = default_col_;
}