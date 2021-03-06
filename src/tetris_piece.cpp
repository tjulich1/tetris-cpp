// Trent Julich ~ 03/02/2021

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

PieceState TetrisPiece::get_next_state() {
  return states_[(current_state_+1)%states_.size()];
}

PieceState TetrisPiece::get_prev_state() {
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

int TetrisPiece::get_col() {
  return col_;
}

int TetrisPiece::get_row() {
  return row_;
}
