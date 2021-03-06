// Trent Julich ~ 03/02/2021

#ifndef PIECE_GENERATOR_H
#define PIECE_GENERATOR_H

#include "tetris_piece.hpp"

class PieceGenerator {
  public: 
    TetrisPiece GetPiece();
  private:
    TetrisPiece CreateZBlock();
    TetrisPiece CreateSBlock();
    TetrisPiece CreateOBlock();
    TetrisPiece CreateIBlock();
    TetrisPiece CreateLBlock();
    TetrisPiece CreateJBlock();
    TetrisPiece CreateTBlock();
};

#endif