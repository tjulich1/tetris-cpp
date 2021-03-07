// Trent Julich ~ 03/02/2021

#include "tetris_game.hpp"
#include "user_input.hpp"
#include "block.hpp"
#include <iostream>

enum UserEventCodes {
  DROP,
};

enum StateCodes {
  CURRENT_STATE,
  CLOCKWISE_STATE,
  COUNTER_CLOCKWISE_STATE
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
				if (e.user.code == DROP) {
          MoveDown();
        }
			} else {
        HandleUserInput(e);
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

void TetrisGame::NextPiece() {
  // Lock the current piece into the board.
  LockPiece();

  // Then spawn a new piece
  current_piece_ = generator_.GetPiece();
}

void TetrisGame::MoveDown() {
  if (IsLegalMove(CURRENT_STATE, 1, 0)) {
    current_piece_.Down();
  } else {
    NextPiece();
  }
}

void TetrisGame::MoveRight() {
  if (IsLegalMove(CURRENT_STATE, 0, 1)) {
    current_piece_.Right();
  } 
}

void TetrisGame::MoveLeft() {
  if (IsLegalMove(CURRENT_STATE, 0, -1)) {
    current_piece_.Left();
  }
}

void TetrisGame::RotateClockwise() {
  if (IsLegalMove(CLOCKWISE_STATE, 0, 0)) {
    current_piece_.Clockwise();
  }
}

void TetrisGame::RotateCounterClockwise() {
  if (IsLegalMove(COUNTER_CLOCKWISE_STATE, 0, 0)) {
    current_piece_.CounterClockwise();
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

bool TetrisGame::IsPieceInBounds(PieceState p_state_to_check, int p_row_transform, int p_col_transform) {
  bool in_bounds = true;
  Block current_block;
  for (int i = 0; i < p_state_to_check.blocks.size(); i++) {
    current_block = p_state_to_check.blocks[i];
    int row = current_piece_.get_row() + current_block.y + p_row_transform;
    int col = current_piece_.get_col() + current_block.x + p_col_transform;
    if (row >= board_.get_rows() || col >= board_.get_cols() || col < 0) {
      in_bounds = false;
    }
  }
  return in_bounds;
}

bool TetrisGame::CheckCollisions(PieceState p_state_to_check, int p_row_transform, int p_col_transform) {
  bool collisions = false;
  Block current_block;
  for (int i = 0; i < p_state_to_check.blocks.size(); i++) {
    current_block = p_state_to_check.blocks[i];
    int row = current_piece_.get_row() + current_block.y + p_row_transform;
    int col = current_piece_.get_col() + current_block.x + p_col_transform;
    if (board_.IsBlockFilled(row, col)) {
      collisions = true;
      break;
    }
  }
  return collisions;
}

bool TetrisGame::IsLegalMove(int p_state_number, int p_row_transform, int p_col_transform) {
  bool legal = true;
  PieceState state;
  switch (p_state_number) {
    case CURRENT_STATE:
      state = current_piece_.get_current_state();
      break;
    case CLOCKWISE_STATE:
      state = current_piece_.get_next_state();
      break;
    case COUNTER_CLOCKWISE_STATE:
      state = current_piece_.get_prev_state();
      break;
    default:
      state = current_piece_.get_current_state();
  }

  // Move is not legal if it goes out of bounds, or if it hits other blocks.
  if (!IsPieceInBounds(state, p_row_transform, p_col_transform) 
    || CheckCollisions(state, p_row_transform, p_col_transform)) {
    legal = false;
  }

  return legal;
}