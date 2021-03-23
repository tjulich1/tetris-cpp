// Trent Julich ~ 03/02/2021

#include "tetris_game.hpp"
#include "block.hpp"
#include <iostream>

TetrisGame::TetrisGame(SDL_Renderer* p_renderer) : renderer_(p_renderer) {
  board_ = TetrisBoard(x_padding_, y_padding_, kBlockDim);
  held_piece_box_ = HeldPieceBox(SDL_Rect{2*x_padding_ + (kBlockDim*board_.get_cols()),
    y_padding_, 100, 100});
  block_color_map_ = new std::map<char, SDL_Color>();
  InitColorMap();

  current_piece_ = generator_.GetPiece();
  current_piece_.SetXOffset(x_padding_);
  current_piece_.SetYOffset(y_padding_);
  current_piece_.SetBlockDim(kBlockDim);

  font_ = TTF_OpenFont("OpenSans-Regular.ttf", 40);
  SDL_Surface* surface_message = TTF_RenderText_Solid(font_, "Pause", {0,0,0});
  pause_message_ = SDL_CreateTextureFromSurface(renderer_, surface_message);
  SDL_FreeSurface(surface_message);
  paused_ = false;
  score_ = 0;
}

TetrisGame::~TetrisGame() {
  SDL_DestroyTexture(pause_message_);
  TTF_CloseFont(font_);
  delete block_color_map_;
}

/*
  Initializes map with characters mapping to RGB colors. Each char corresponds to a type of block 
  that can appear on the game board.
*/
void TetrisGame::InitColorMap() {
  block_color_map_->insert({'j', SDL_Color{3, 65, 174}});
  block_color_map_->insert({'s', SDL_Color{114, 203, 59}});
  block_color_map_->insert({'o', SDL_Color{255, 213, 0}});
  block_color_map_->insert({'l', SDL_Color{255, 151, 28}});
  block_color_map_->insert({'z', SDL_Color{255, 50, 19}});
  block_color_map_->insert({'t', SDL_Color{128, 77, 198}});
  block_color_map_->insert({'i', SDL_Color{27, 222, 228}});
}

void TetrisGame::RenderPause() {
  SDL_Color black = {0, 0, 0};
  SDL_Rect message_rect{x_padding_, y_padding_, board_.get_cols()*kBlockDim, kBlockDim*board_.get_rows()/4};
  SDL_RenderCopy(renderer_, pause_message_, NULL, &message_rect);
}

void TetrisGame::Render() {
  int rows = board_.get_rows();
  int cols = board_.get_cols();

  SDL_Rect rect;

  SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
  SDL_RenderClear(renderer_);

  held_piece_box_.Render(renderer_, block_color_map_);

  if (paused_) {
    RenderPause();
  } else {
    // Draw board
    board_.Render(renderer_, block_color_map_);

    // Draw the current piece
    current_piece_.Render(renderer_, block_color_map_);
  }
  SDL_RenderPresent(renderer_);
}

void TetrisGame::NextPiece() {
  // Lock the current piece into the board.
  board_.LockPiece(current_piece_);

  // Clear any rows that are completed.
  AddScore(board_.ClearRows());

  // Then spawn a new piece
  current_piece_ = generator_.GetPiece();
  current_piece_.SetXOffset(x_padding_);
  current_piece_.SetYOffset(y_padding_);
  current_piece_.SetBlockDim(kBlockDim);

  can_swap_ = true;

  // Check to ensure that the new piece can at least move down once, or else end the game.
  bool should_continue_game = IsLegalMove(CURRENT_STATE, 1, 0);
  if (!should_continue_game) {
    SDL_Event e;
    e.type = SDL_QUIT;
    SDL_PushEvent(&e);
  }
}

void TetrisGame::TogglePause() {
  paused_ = !paused_;
}

bool TetrisGame::IsPaused() {
  return paused_;
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

void TetrisGame::SwapPiece() {
  if (can_swap_) {
    can_swap_ = false;
    TetrisPiece temp = current_piece_;
    
    // held_piece_ would only have this type if a swap hasn't occurred yet, i.e. held_piece_ doesn't
    // have a set block type and gets the default type '-'.
    if (held_piece_.get_type() == '-') {
      held_piece_ = current_piece_;
      held_piece_box_.SetHeldPiece(held_piece_);
      current_piece_ = generator_.GetPiece();
      current_piece_.SetXOffset(x_padding_);
      current_piece_.SetYOffset(y_padding_);
      current_piece_.SetBlockDim(kBlockDim);
    } else {
      TetrisPiece temp = held_piece_;
      held_piece_ = current_piece_;
      held_piece_box_.SetHeldPiece(held_piece_);
      current_piece_ = temp;
      current_piece_.ResetPosition();
    }
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
      break;
    }
  }
  return in_bounds;
}

void TetrisGame::AddScore(int p_rows_cleared) {
  score_ += p_rows_cleared * 100;
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

bool TetrisGame::IsLegalMove(StateCode p_state_code, int p_row_transform, int p_col_transform) {
  bool legal = true;
  PieceState state;
  switch (p_state_code) {
    case CURRENT_STATE:
      state = current_piece_.get_current_state();
      break;
    case CLOCKWISE_STATE:
      state = current_piece_.get_clockwise_state();
      break;
    case COUNTER_CLOCKWISE_STATE:
      state = current_piece_.get_counter_clockwise_state();
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