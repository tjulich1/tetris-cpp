#include "held_piece_box.hpp"

HeldPieceBox::HeldPieceBox(int p_x_offset, int p_y_offset, int p_width, int p_height)
  : x_offset_(p_x_offset), y_offset_(p_y_offset), width_(p_width), height_(p_height) { }

void HeldPieceBox::SetHeldPiece(TetrisPiece p_held_piece) {
  held_piece_ = p_held_piece;
  int piece_dim = height_ / 5;
  held_piece_.SetXOffset(x_offset_ + (width_ - held_piece_.get_current_state().width*piece_dim) / 2);
  held_piece_.SetYOffset(y_offset_ + (height_ - held_piece_.get_current_state().height*piece_dim) / 2);
  held_piece_.SetBlockDim(piece_dim);
  held_piece_.SetCol(0);
  held_piece_.SetRow(0);
}

void HeldPieceBox::Render(SDL_Renderer* p_renderer, std::map<char, SDL_Color>* p_colors) {

  // Draw the border of the box
  SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, 255);
  SDL_Rect bounds{x_offset_ - 1, y_offset_ - 1, width_ + 2, height_ + 2};
  SDL_RenderDrawRect(p_renderer, &bounds);

  if (held_piece_.get_type() != '-') {
    held_piece_.Render(p_renderer, p_colors);
  }
}