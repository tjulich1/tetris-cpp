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
    TetrisPiece(const std::vector<PieceState> p_states);
    TetrisPiece();
  
    void Right();
    void Left();
    void Down();

    PieceState get_current_state();
    int get_row();
    int get_col();
  private:
    int row_;
    int col_;
    std::vector<PieceState> states_;
    int current_state_;
};

#endif