// Trent Julich ~ 03/02/2021

#ifndef TETRIS_PIECE_H
#define TETRIS_PIECE_H

#include <vector>
#include <map>
#include <SDL.h>
#include "block.hpp"

struct PieceState {
  std::vector<Block> blocks;
  int width; 
  int height;
};

class TetrisPiece {
  public: 
    TetrisPiece(const std::vector<PieceState> p_states, char p_piece_type);
    TetrisPiece();
  
    // Transformations to Tetris Piece
    void Right();
    void Left();
    void Down();
    void Clockwise();
    void CounterClockwise();
    void ResetPosition();

    void SetXOffset(int p_x_offset);
    void SetYOffset(int p_y_offset);
    void SetBlockDim(int p_block_dim);
    void SetCol(int p_col);
    void SetRow(int p_row);
    void Render(SDL_Renderer* p_renderer, std::map<char, SDL_Color>* p_colors);

    PieceState get_current_state();
    PieceState get_clockwise_state();
    PieceState get_counter_clockwise_state();

    int get_row();
    int get_col();
    char get_type();
  private:
    const static int default_col_ = 4;
    

    int row_;
    int col_;
    int x_offset_;
    int y_offset_;
    int block_dim_;
    std::vector<PieceState> states_;
    int current_state_;
    char piece_type_;
};

#endif