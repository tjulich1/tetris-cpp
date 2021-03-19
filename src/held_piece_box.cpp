#include "held_piece_box.hpp"

HeldPieceBox::HeldPieceBox(int p_x_offset, int p_y_offset, int p_width, int p_height)
  : x_offset_(p_x_offset), y_offset_(p_y_offset), width_(p_width), height_(p_height) { }

void HeldPieceBox::SetHeldPiece(TetrisPiece p_held_piece) {
  held_piece_ = p_held_piece;
}

void HeldPieceBox::Render(SDL_Renderer* p_renderer, std::map<char, SDL_Color>* p_colors) {

  // Draw the border of the box
  SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, 255);
  SDL_Rect bounds{x_offset_ - 1, y_offset_ - 1, width_ + 2, height_ + 2};
  SDL_RenderDrawRect(p_renderer, &bounds);

  if (held_piece_.get_type() != '-') {
    SDL_Color piece_color = p_colors->find(held_piece_.get_type())->second;
    SDL_SetRenderDrawColor(p_renderer, piece_color.r, piece_color.g, piece_color.b, 255);

    int piece_dim = height_ / 5;
    int piece_start_x = x_offset_ + (width_ - held_piece_.get_current_state().width*piece_dim) / 2;
    int piece_start_y = y_offset_ + (height_ - held_piece_.get_current_state().height*piece_dim) / 2;

    std::vector<Block> blocks = held_piece_.get_current_state().blocks;
    for (int i = 0; i < blocks.size(); i++) {
      Block current_block = blocks[i];
      SDL_Rect rect{
        piece_start_x + current_block.x*piece_dim,
        piece_start_y + current_block.y*piece_dim,
        piece_dim, 
        piece_dim
      };
      SDL_RenderFillRect(p_renderer, &rect);
    }
  }
}