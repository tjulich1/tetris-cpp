#ifndef HELD_PIECE_BOX_HPP
#define HELD_PIECE_BOX_HPP

#include <SDL.h>
#include <map>
#include "tetris_piece.hpp"
#include "render_box.hpp"

class HeldPieceBox : public RenderBox {
  public: 
    HeldPieceBox(SDL_Rect p_bounds);
    void Render(SDL_Renderer* p_renderer_, std::map<char, SDL_Color>* p_colors) override;
    void SetHeldPiece(TetrisPiece p_held_piece);
  private:
    TetrisPiece held_piece_;
};

#endif