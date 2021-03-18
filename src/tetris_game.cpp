// Trent Julich ~ 03/02/2021

#include "tetris_game.hpp"
#include "block.hpp"

#include <iostream>

int x_offset = 50;
int y_offset = 50;

TetrisGame::TetrisGame(SDL_Renderer* p_renderer) : renderer_(p_renderer) {
  board_ = TetrisBoard(x_offset, y_offset, kBlockDim);
  block_color_map_ = new std::map<char, SDL_Color>();
  InitColorMap();
  current_piece_ = generator_.GetPiece();

  font_ = TTF_OpenFont("OpenSans-Regular.ttf", 40);
  SDL_Surface* surface_message = TTF_RenderText_Solid(font_, "Pause", {0,0,0});
  pause_message_ = SDL_CreateTextureFromSurface(renderer_, surface_message);
  SDL_FreeSurface(surface_message);
  paused_ = false;
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
  SDL_Rect message_rect{0, 0, 200, 120};
  SDL_RenderCopy(renderer_, pause_message_, NULL, &message_rect);
}

void TetrisGame::Render() {
  int rows = board_.get_rows();
  int cols = board_.get_cols();

  SDL_Rect rect;

  SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
  SDL_RenderClear(renderer_);

  if (paused_) {
    RenderPause();
  } else {
    // Draw board
    board_.Render(renderer_, block_color_map_);

    PieceState cur_state = current_piece_.get_current_state();
    // Lookup the color of the current piece.
    SDL_Color block_color = block_color_map_->find(current_piece_.get_type())->second;
    SDL_SetRenderDrawColor(renderer_, block_color.r, block_color.g, block_color.b, 255);

    // Draw each of the blocks of the current piece.
    for (int i = 0; i < cur_state.blocks.size(); i++) {
      Block current_block = cur_state.blocks[i];
      rect = {
        x_offset + (current_piece_.get_col()+current_block.x)*kBlockDim,
        y_offset + (current_piece_.get_row()+current_block.y)*kBlockDim,
        kBlockDim,
        kBlockDim
      };
      SDL_RenderFillRect(renderer_, &rect);
    }
  }
  SDL_RenderPresent(renderer_);
}

void TetrisGame::NextPiece() {
  // Lock the current piece into the board.
  board_.LockPiece(current_piece_);

  // Clear any rows that are completed.
  board_.ClearRows();

  // Then spawn a new piece
  current_piece_ = generator_.GetPiece();

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