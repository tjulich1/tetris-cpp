// Trent Julich ~ 03/02/2021

#include "piece_generator.hpp"
#include "block.hpp"

#include <iostream>
#include <vector>
#include <cstdlib>


TetrisPiece PieceGenerator::GetPiece() {
  int rand_num = rand() % 3;
  TetrisPiece piece;
  switch(rand_num) {
    case 0:
      piece = CreateOBlock();
      break;
    case 1:
      piece = CreateZBlock();
      break;
    case 2:
      piece = CreateSBlock();
      break;
    default:
      piece = CreateOBlock();
  }
  return piece;
}

TetrisPiece PieceGenerator::CreateOBlock() {
  std::vector<Block> o_blocks{
    Block{0, 0, 'o'},
    Block{1, 0, 'o'},
    Block{0, 1, 'o'},
    Block{1, 1, 'o'}
  };

  int width = 2;
  int height = 2;

  PieceState o_block_state{
    o_blocks, width, height
  };

  return TetrisPiece(std::vector<PieceState>{
    o_block_state
  });
}

TetrisPiece PieceGenerator::CreateZBlock() {
  std::vector<Block> first_z_state_blocks{
    Block{0, 0, 'z'},
    Block{1, 0, 'z'},
    Block{1, 1, 'z'},
    Block{2, 1, 'z'}
  };
  std::vector<Block> second_z_state_blocks{
    Block{1, 0, 'z'}, 
    Block{0, 1, 'z'}, 
    Block{1, 1, 'z'},
    Block{0, 2, 'z'}
  };

  int state_width;
  int state_height;

  // The width and height of the first z state
  state_width = 3;
  state_height = 2;
  
  // Create the first state
  PieceState first_state{
    first_z_state_blocks, state_width, state_height
  };
   
  // The width and height of the second z state;
  state_width = 2;
  state_height = 3;

  // Create the second state
  PieceState second_state{
    second_z_state_blocks, state_width, state_height
  };

  return TetrisPiece(std::vector<PieceState>{
    first_state, second_state
  });
}

TetrisPiece PieceGenerator::CreateSBlock() {
  std::vector<Block> state_one_blocks{
    Block{1, 0, 's'},
    Block{2, 0, 's'},
    Block{0, 1, 's'},
    Block{1, 1, 's'}
  };

  std::vector<Block> state_two_blocks{
    Block{0, 0, 's'},
    Block{0, 1, 's'},
    Block{1, 1, 's'},
    Block{1, 2, 's'}
  };

  int state_width;
  int state_height;

  state_width = 3;
  state_height = 2;

  PieceState first_state{
    state_one_blocks, state_width, state_height
  };

  state_width = 2;
  state_height = 3;

  PieceState second_state{
    state_two_blocks, state_width, state_height
  };

  return TetrisPiece(std::vector<PieceState>{
    first_state, second_state
  });
}
