#include "tetris_game.hpp"
#include <iostream>

TetrisGame::TetrisGame(SDL_Renderer* p_renderer) {
  renderer_ = p_renderer;
  current_piece_ = generator_.GetPiece();
  board_.SetBlock(19, 9, 'w');
  std::cout << board_.IsBlockFilled(19, 9) << board_.IsBlockFilled(18, 9) << std::endl;;
  board_.PrintBoard();
}

TetrisGame::~TetrisGame() {
  
}

void TetrisGame::Render() {
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
  PieceState cur_state = current_piece_.get_current_state();
  int rows = board_.get_rows();
  int cols = board_.get_cols();

  SDL_Rect rect;

  // Draw board perimeter
  SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255);
  SDL_RenderDrawLine(renderer_, 0, kBlockDim*board_.get_rows(),
    kBlockDim*board_.get_cols(), kBlockDim*board_.get_rows());
  SDL_RenderDrawLine(renderer_, kBlockDim*board_.get_cols(), 0, 
    kBlockDim*board_.get_cols(), kBlockDim*board_.get_rows());
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);

  // Draw board
  for (int i = 0; i < rows; i++) {
    for(int j = 0; j < cols; j++) {
      if (board_.IsBlockFilled(i, j)) {
        rect = {
          j*kBlockDim,
          i*kBlockDim,
          kBlockDim,
          kBlockDim
        };
        SDL_RenderFillRect(renderer_, &rect);
      }
    }
  }

  // Draw current block
  for (int i = 0; i < cur_state.blocks.size(); i++) {
    Block current_block = cur_state.blocks[i];
    rect = {
      (current_piece_.get_col()+current_block.x)*kBlockDim,
      (current_piece_.get_row()+current_block.y)*kBlockDim,
      kBlockDim,
      kBlockDim
    };
    SDL_RenderFillRect(renderer_, &rect);
  }
}

void TetrisGame::MoveDown() {
  if (current_piece_.get_current_state().height + current_piece_.get_row() < board_.get_rows()) {
    current_piece_.Down();
  }
}

void TetrisGame::MoveRight() {
  if (current_piece_.get_col() + current_piece_.get_current_state().width < board_.get_cols()) {
    current_piece_.Right();
  }
}

void TetrisGame::MoveLeft() {
  if (current_piece_.get_col() > 0) {
    current_piece_.Left();
  }
}