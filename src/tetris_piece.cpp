#include "tetris_piece.hpp"
#include <iostream>

TetrisPiece::TetrisPiece(const std::vector<PieceState> p_states) {
  current_state_ = 0;
  states_ = p_states;
  row_ = 0;
  col_ = 0;
}

TetrisPiece::TetrisPiece() {
  current_state_ = -1;
  row_ = 0;
  col_ = 0;
}

PieceState TetrisPiece::get_current_state() {
  if (current_state_ != -1) {
    return states_[current_state_];
  } else {
    return states_[0];
  }
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

int TetrisPiece::get_col() {
  return col_;
}

int TetrisPiece::get_row() {
  return row_;
}
