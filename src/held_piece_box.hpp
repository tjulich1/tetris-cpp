#include <SDL.h>
#include "tetris_piece.hpp"
#include <map>

class HeldPieceBox {
  public: 
    HeldPieceBox(int p_x_offset, int p_y_offset, int p_width, int p_height);
    void Render(SDL_Renderer* p_renderer_, std::map<char, SDL_Color>* p_colors);
    void SetHeldPiece(TetrisPiece p_held_piece);
  private:
    TetrisPiece held_piece_;
    int x_offset_;
    int y_offset_;
    int width_;
    int height_;
};
