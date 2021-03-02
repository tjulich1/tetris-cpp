// Trent Julich ~ 03/02/2021

#include "piece_generator.hpp"
#include <iostream>

TetrisPiece PieceGenerator::GetPiece() {
  return CreateZBlock();
}

TetrisPiece PieceGenerator::CreateZBlock() {
  std::vector<Block> first_z_state_blocks{
    Block{1, 0, 'z'}, 
    Block{0, 1, 'z'}, 
    Block{1, 1, 'z'},
    Block{0, 2, 'z'}
  };
  std::vector<Block> second_z_state_blocks{
    Block{0, 0, 'z'},
    Block{1, 0, 'z'},
    Block{1, 1, 'z'},
    Block{2, 1, 'z'}
  };

  int state_width;
  int state_height;

  // The width and height of the first z state
  state_width = 2;
  state_height = 3;
  
  // Create the first state
  PieceState first_state = PieceState{
    first_z_state_blocks, state_width, state_height
  };
   
  
  // The width and height of the second z state;
  state_width = 3;
  state_height = 2;

  // Create the second state
  PieceState second_state = PieceState{
    second_z_state_blocks, state_width, state_height
  };

  return TetrisPiece(std::vector<PieceState>{
    first_state, second_state
  });
}
