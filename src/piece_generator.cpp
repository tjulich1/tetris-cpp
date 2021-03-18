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
    Block{0, 0},
    Block{1, 0},
    Block{0, 1},
    Block{1, 1}
  };

  int width = 2;
  int height = 2;

  PieceState o_block_state{
    o_blocks, width, height
  };

  return TetrisPiece(std::vector<PieceState>{ o_block_state }, 'o');
}

TetrisPiece PieceGenerator::CreateZBlock() {
  std::vector<Block> first_z_state_blocks{
    Block{0, 0},
    Block{1, 0},
    Block{1, 1},
    Block{2, 1}
  };
  std::vector<Block> second_z_state_blocks{
    Block{1, 0}, 
    Block{0, 1}, 
    Block{1, 1},
    Block{0, 2}
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

  return TetrisPiece(std::vector<PieceState>{ first_state, second_state }, 'z');
}

TetrisPiece PieceGenerator::CreateSBlock() {
  std::vector<Block> state_one_blocks{
    Block{1, 0},
    Block{2, 0},
    Block{0, 1},
    Block{1, 1}
  };

  std::vector<Block> state_two_blocks{
    Block{0, 0},
    Block{0, 1},
    Block{1, 1},
    Block{1, 2}
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

  return TetrisPiece(std::vector<PieceState>{ first_state, second_state }, 's');
}

TetrisPiece PieceGenerator::CreateIBlock() {
  std::vector<Block> state_one_blocks{
    Block{0, 0},
    Block{0, 1},
    Block{0, 2},
    Block{0, 3}
  };

  std::vector<Block> state_two_blocks{
    Block{0, 0},
    Block{1, 0},
    Block{2, 0},
    Block{3, 0}
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

  return TetrisPiece(std::vector<PieceState>{ first_state, second_state }, 'i');
}

TetrisPiece PieceGenerator::CreateLBlock() {
  std::vector<Block> first_state_blocks{
    Block{0, 0},
    Block{0, 1},
    Block{0, 2},
    Block{1, 2}
  };

  std::vector<Block> second_state_blocks{
    Block{0, 0},
    Block{1, 0},
    Block{2, 0},
    Block{0, 1}
  };

  std::vector<Block> third_state_blocks{
    Block{0, 0},
    Block{1, 0},
    Block{1, 1},
    Block{1, 2}
  };

  std::vector<Block> fourth_state_blocks{
    Block{2, 0},
    Block{0, 1},
    Block{1, 1},
    Block{2, 1}
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

  return TetrisPiece(
    std::vector<PieceState>{ first_state, second_state, third_state, fourth_state }, 'l');
}

TetrisPiece PieceGenerator::CreateJBlock() {
  std::vector<Block> first_state_blocks{
    Block{1, 0},
    Block{1, 1},
    Block{1, 2},
    Block{0, 2}
  };

  std::vector<Block> second_state_blocks{
    Block{0, 0},
    Block{0, 1},
    Block{1, 1},
    Block{2, 1}
  };

  std::vector<Block> third_state_blocks{
    Block{0, 0},
    Block{1, 0},
    Block{0, 1},
    Block{0, 2}
  };

  std::vector<Block> fourth_state_blocks{
    Block{0, 0},
    Block{1, 0},
    Block{2, 0},
    Block{2, 1}
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

  return TetrisPiece(
    std::vector<PieceState>{ first_state, second_state, third_state, fourth_state}, 'j');
}

TetrisPiece PieceGenerator::CreateTBlock() {
  std::vector<Block> first_state_blocks{
    Block{1, 0},
    Block{0, 1},
    Block{1, 1},
    Block{2, 1}
  };

  std::vector<Block> second_state_blocks{
    Block{0, 0},
    Block{0, 1},
    Block{0, 2},
    Block{1, 1}
  };
  std::vector<Block> third_state_blocks{
    Block{0, 0},
    Block{1, 0},
    Block{2, 0},
    Block{1, 1}
  };
  std::vector<Block> fourth_state_blocks{
    Block{1, 0},
    Block{1, 1},
    Block{1, 2},
    Block{0, 1}
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

  return TetrisPiece(
    std::vector<PieceState>{ first_state, second_state, third_state, fourth_state }, 't');

}