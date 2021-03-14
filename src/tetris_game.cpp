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
  InitColorMap();
  current_piece_ = generator_.GetPiece();
  paused_ = false;
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
      // Ensure that the game is not paused.
			} else if (!paused_) {
        if (e.type == SDL_USEREVENT) {
				  if (e.user.code == DROP) {
            MoveDown();
          }
			  } else {
          HandleUserInput(e);
        }
        SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
		    SDL_RenderClear(renderer_);
		    Render();
		    SDL_RenderPresent(renderer_);
      // If the game IS paused
      } else {
        // Only handle button pressed to unpause the game.
        SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
        SDL_RenderClear(renderer_);
        RenderPause();
        SDL_RenderPresent(renderer_);
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
          paused_ = false;
        }
      }
    } 
    
	}

}

/*
  Initializes map with characters mapping to RGB colors. Each char corresponds to a type of block 
  that can appear on the game board.
*/
void TetrisGame::InitColorMap() {
  block_color_map_.insert({'j', SDL_Color{3, 65, 174}});
  block_color_map_.insert({'s', SDL_Color{114, 203, 59}});
  block_color_map_.insert({'o', SDL_Color{255, 213, 0}});
  block_color_map_.insert({'l', SDL_Color{255, 151, 28}});
  block_color_map_.insert({'z', SDL_Color{255, 50, 19}});
  block_color_map_.insert({'t', SDL_Color{128, 77, 198}});
  block_color_map_.insert({'i', SDL_Color{27, 222, 228}});
}

void TetrisGame::RenderPause() {
  
}

void TetrisGame::Render() {
  int current_r;
  int current_g;
  int current_b;

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
  SDL_Color block_color;
  for (int i = 0; i < rows; i++) {
    for(int j = 0; j < cols; j++) {
      if (board_.IsBlockFilled(i, j)) {
        block_color = block_color_map_.find(board_.GetBlock(i, j))->second;
        current_r = block_color.r;
        current_g = block_color.g;
        current_b = block_color.b;
        SDL_SetRenderDrawColor(renderer_, current_r, current_g, current_b, 255);
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

  PieceState cur_state = current_piece_.get_current_state();

  // Lookup the color of the current piece.
  block_color = block_color_map_.find(cur_state.blocks[0].block_code)->second;
  current_r = block_color.r;
  current_g = block_color.g;
  current_b = block_color.b;
  SDL_SetRenderDrawColor(renderer_, current_r, current_g, current_b, 255);

  // Draw each of the blocks of the current piece.
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

  // Clear any rows that are completed.
  board_.ClearRows();

  // Then spawn a new piece
  current_piece_ = generator_.GetPiece();
}

void TetrisGame::Pause() {
  paused_ = true;
}

bool TetrisGame::MoveDown() {
  bool success = true;
  if (IsLegalMove(CURRENT_STATE, 1, 0)) {
    current_piece_.Down();
  } else {
    NextPiece();
    success = false;
  }
  return success;
}

void TetrisGame::DropPiece() {
  while(MoveDown()) { }
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