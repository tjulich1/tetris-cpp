// Trent Julich ~ 03/02/2021

#ifndef TETRIS_PIECE_H
#define TETRIS_PIECE_H

#include <vector>
#include "block.hpp"

struct PieceState {
  std::vector<Block> blocks;
  int width; 
  int height;
};

class TetrisPiece {
  public: 
    TetrisPiece(const std::vector<PieceState> p_states, char p_piece_type);
    TetrisPiece();
  
    void Right();
    void Left();
    void Down();
    void Clockwise();
    void CounterClockwise();

    PieceState get_current_state();
    PieceState get_next_state();
    PieceState get_prev_state();
    int get_row();
    int get_col();
    char get_type();
  private:
    int row_;
    int col_;
    std::vector<PieceState> states_;
    int current_state_;
    char piece_type_;
};

#endif