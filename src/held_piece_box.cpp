#include "held_piece_box.hpp"

HeldPieceBox::HeldPieceBox(SDL_Rect p_bounds) : RenderBox(p_bounds) {}

void HeldPieceBox::SetHeldPiece(TetrisPiece p_held_piece) {
  held_piece_ = p_held_piece;
  int piece_dim = bounds_.h / 5;
  held_piece_.SetXOffset(bounds_.x + (bounds_.w - held_piece_.get_current_state().width*piece_dim) / 2);
  held_piece_.SetYOffset(bounds_.y + (bounds_.h - held_piece_.get_current_state().height*piece_dim) / 2);
  held_piece_.SetBlockDim(piece_dim);
  held_piece_.SetCol(0);
  held_piece_.SetRow(0);
}

void HeldPieceBox::Render(SDL_Renderer* p_renderer, std::map<char, SDL_Color>* p_colors) {
  // Draw the border of the box
  SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, 255);
  SDL_Rect temp_bounds{bounds_.x - 1, bounds_.y - 1, bounds_.w + 2, bounds_.h + 2};
  SDL_RenderDrawRect(p_renderer, &temp_bounds);

  if (held_piece_.get_type() != '-') {
    held_piece_.Render(p_renderer, p_colors);
  }
}