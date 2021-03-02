// Trent Julich ~ 03/02/2021

#include "tetris_game.hpp"
#include "user_input.hpp"
#include <iostream>

enum UserEventCodes {
  DROP,
};

unsigned int Tick(unsigned int p_interval, void* p_params) {
  std::cout << "Game Tick" << std::endl;
  SDL_Event drop_event;
  SDL_UserEvent drop_user_event;
  drop_user_event.type = SDL_USEREVENT;
  drop_user_event.code = DROP;
  drop_event.type = SDL_USEREVENT;
  drop_event.user = drop_user_event;

  SDL_PushEvent(&drop_event);

  return p_interval;
}

TetrisGame::TetrisGame(SDL_Renderer* p_renderer) {
  renderer_ = p_renderer;
  current_piece_ = generator_.GetPiece();
  board_.SetBlock(19, 9, 'w');
  std::cout << board_.IsBlockFilled(19, 9) << board_.IsBlockFilled(18, 9) << std::endl;;
}

// Main Tetris game loop.
void TetrisGame::StartGame() {
  SDL_Event e;
  bool quit = false;
  SDL_TimerID timer = SDL_AddTimer(3000, Tick, NULL);
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			// Exit game if exit command is given.
			if (e.type == SDL_QUIT) {
				quit = true;
			} else if (e.type == SDL_USEREVENT) {
        std::cout << "In user event" << std::endl;
				if (e.user.code == DROP) {
          MoveDown();
        }
			} else {
        handleUserInput(e);
      }
    } 
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
		SDL_RenderClear(renderer_);
		Render();
		SDL_RenderPresent(renderer_);
	}
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

bool TetrisGame::IsUnderPieceClear() {
  bool under_piece_clear = true;

  int current_piece_row = current_piece_.get_row();
  int current_piece_col = current_piece_.get_col();

  int current_block_row;
  int current_block_col;

  PieceState current_state = current_piece_.get_current_state();
  for (int i = 0; i < current_state.blocks.size(); i++) {
    std::cout << "Block " << i << std::endl;
    Block current_block = current_state.blocks[i];
    current_block_row = current_piece_row + current_block.y;
    current_block_col = current_piece_col + current_block.x;
    
    // Check on board if under each block is clear
    if (board_.IsBlockFilled(current_block_row + 1, current_block_col)) {
      under_piece_clear = false;
      break;
    }
  }
  return under_piece_clear;
}

void TetrisGame::NextPiece() {
  // Lock the current piece into the board.
  LockPiece();

  // Then spawn a new piece
  current_piece_ = generator_.GetPiece();
}

void TetrisGame::MoveDown() {
  // Check if the current piece is not at the bottom of the board
  if (current_piece_.get_current_state().height + current_piece_.get_row() < board_.get_rows()) {
    if (IsUnderPieceClear()) {
      current_piece_.Down();
    } else {
      NextPiece();
    }
  } else {
    NextPiece();
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

void TetrisGame::LockPiece() {
  // Grab the current state of the piece to lock.
  PieceState current_state = current_piece_.get_current_state();
  for (int i = 0; i < current_state.blocks.size(); i++) {
    // Grab the first block of the piece state.
    Block current_block = current_state.blocks[i];
    
    // Find the actual (x, y) coords of the current block on the board.
    int current_block_global_x = current_block.x + current_piece_.get_col();
    int current_block_global_y = current_block.y + current_piece_.get_row();
    
    // Update the board and mark where current block is.
    board_.SetBlock(current_block_global_y, current_block_global_x, current_block.block_code);
  }
}