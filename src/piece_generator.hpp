#ifndef PIECE_GENERATOR_H
#define PIECE_GENERATOR_H

#include "tetris_piece.hpp"
#include <vector>
#include <map>

class PieceGenerator {
  public: 
    TetrisPiece GetPiece();
  private:
    TetrisPiece CreateZBlock();
};

#endif