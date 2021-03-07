// Trent Julich ~ 03/02/2021

#include "piece_generator.hpp"
#include "block.hpp"

#include <iostream>
#include <vector>
#include <cstdlib>


TetrisPiece PieceGenerator::GetPiece() {
  int number_of_pieces = 7;
  int rand_num = rand() % number_of_pieces;
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
    case 3:
      piece = CreateIBlock();
      break;
    case 4:
      piece = CreateLBlock();
      break;
    case 5:
      piece = CreateJBlock();
      break;
    case 6: 
      piece = CreateTBlock();
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

TetrisPiece PieceGenerator::CreateIBlock() {
  std::vector<Block> state_one_blocks{
    Block{0, 0, 'i'},
    Block{0, 1, 'i'},
    Block{0, 2, 'i'},
    Block{0, 3, 'i'}
  };

  std::vector<Block> state_two_blocks{
    Block{0, 0, 'i'},
    Block{1, 0, 'i'},
    Block{2, 0, 'i'},
    Block{3, 0, 'i'}
  };

  int state_width;
  int state_height;

  state_width = 1;
  state_height = 4;

  PieceState first_state{
    state_one_blocks, state_width, state_height
  };

  state_width = 4;
  state_height = 1;

  PieceState second_state{
    state_two_blocks, state_width, state_height
  };

  return TetrisPiece(std::vector<PieceState>{
    first_state, second_state
  });
}

TetrisPiece PieceGenerator::CreateLBlock() {
  std::vector<Block> first_state_blocks{
    Block{0, 0, 'l'},
    Block{0, 1, 'l'},
    Block{0, 2, 'l'},
    Block{1, 2, 'l'}
  };

  std::vector<Block> second_state_blocks{
    Block{0, 0, 'l'},
    Block{1, 0, 'l'},
    Block{2, 0, 'l'},
    Block{0, 1, 'l'}
  };

  std::vector<Block> third_state_blocks{
    Block{0, 0, 'l'},
    Block{1, 0, 'l'},
    Block{1, 1, 'l'},
    Block{1, 2, 'l'}
  };

  std::vector<Block> fourth_state_blocks{
    Block{2, 0, 'l'},
    Block{0, 1, 'l'},
    Block{1, 1, 'l'},
    Block{2, 1, 'l'}
  };

  int state_width;
  int state_height;

  state_width = 2;
  state_height = 3;

  PieceState first_state{
    first_state_blocks, state_width, state_height
  };

  PieceState third_state{
    third_state_blocks, state_width, state_height
  };

  state_width = 3;
  state_height = 2;

  PieceState second_state{
    second_state_blocks, state_width, state_height
  };

  PieceState fourth_state{
    fourth_state_blocks, state_width, state_height
  };

  return TetrisPiece(std::vector<PieceState>{
    first_state, second_state, third_state, fourth_state
  });
}

TetrisPiece PieceGenerator::CreateJBlock() {
  std::vector<Block> first_state_blocks{
    Block{1, 0, 'j'},
    Block{1, 1, 'j'},
    Block{1, 2, 'j'},
    Block{0, 2, 'j'}
  };

  std::vector<Block> second_state_blocks{
    Block{0, 0, 'j'},
    Block{0, 1, 'j'},
    Block{1, 1, 'j'},
    Block{2, 1, 'j'}
  };

  std::vector<Block> third_state_blocks{
    Block{0, 0, 'j'},
    Block{1, 0, 'j'},
    Block{0, 1, 'j'},
    Block{0, 2, 'j'}
  };

  std::vector<Block> fourth_state_blocks{
    Block{0, 0, 'j'},
    Block{1, 0, 'j'},
    Block{2, 0, 'j'},
    Block{2, 1, 'j'}
  };

  int state_width;
  int state_height;

  state_width = 2;
  state_height = 3;

  PieceState first_state{
    first_state_blocks, state_width, state_height
  };

  PieceState third_state{
    third_state_blocks, state_width, state_height
  };

  state_width = 3;
  state_height = 2;

  PieceState second_state{
    second_state_blocks, state_width, state_height
  };

  PieceState fourth_state{
    fourth_state_blocks, state_width, state_height
  };

  return TetrisPiece(std::vector<PieceState>{
    first_state, second_state, third_state, fourth_state
  });
}

TetrisPiece PieceGenerator::CreateTBlock() {
  std::vector<Block> first_state_blocks{
    Block{1, 0, 't'},
    Block{0, 1, 't'},
    Block{1, 1, 't'},
    Block{2, 1, 't'}
  };

  std::vector<Block> second_state_blocks{
    Block{0, 0, 't'},
    Block{0, 1, 't'},
    Block{0, 2, 't'},
    Block{1, 1, 't'}
  };
  std::vector<Block> third_state_blocks{
    Block{0, 0, 't'},
    Block{1, 0, 't'},
    Block{2, 0, 't'},
    Block{1, 1, 't'}
  };
  std::vector<Block> fourth_state_blocks{
    Block{1, 0, 't'},
    Block{1, 1, 't'},
    Block{1, 2, 't'},
    Block{0, 1, 't'}
  };

  int state_width = 3;
  int state_height = 2;

  PieceState first_state{
    first_state_blocks, state_width, state_height
  };

  PieceState third_state{
    third_state_blocks, state_width, state_height
  };

  state_width = 2;
  state_height = 3;

  PieceState second_state{
    second_state_blocks, state_width, state_height
  };

  PieceState fourth_state{
    fourth_state_blocks, state_width, state_height
  };

  return TetrisPiece(std::vector<PieceState>{
    first_state, second_state, third_state, fourth_state
  });

}