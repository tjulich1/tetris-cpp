// Trent Julich ~ 03/02/2021

#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include "piece_generator.hpp"
#include "tetris_board.hpp"
#include "tetris_piece.hpp"

#include <map>
#include <SDL.h>
#include <SDL_ttf.h>

const int kBlockDim = 20;
const static int ROWS = 20;
const static int COLS = 10;

unsigned int Tick(unsigned int p_interval, void* p);

enum StateCode {
  CURRENT_STATE,
  CLOCKWISE_STATE,
  COUNTER_CLOCKWISE_STATE
};

class TetrisGame {
  public:
    TetrisGame(SDL_Renderer* p_renderer);
    ~TetrisGame();

    void Render();
    bool IsPaused();
    
    // Methods used to modify the current piece.
    void MoveLeft();
    void MoveRight();
    bool MoveDown();
    void DropPiece();
    void RotateClockwise();
    void RotateCounterClockwise();
    void SwapPiece();
    void TogglePause();
    void StartGame();

  private: 

    SDL_Renderer* renderer_; 
    TTF_Font* font_;
    
    PieceGenerator generator_;
    TetrisBoard board_;
    TetrisPiece current_piece_;
    TetrisPiece held_piece_;
    bool can_swap_ = true;

    std::map<char, SDL_Color>* block_color_map_;
    
    SDL_Texture* pause_message_;

    bool paused_;
    
    void RenderPause();
    unsigned int timer_interval_;

    bool IsPieceInBounds(PieceState p_state_to_check, int p_row_transform, int p_col_transform);
    bool CheckCollisions(PieceState p_state_to_check, int p_row_transform, int p_col_transform);
    bool IsLegalMove(StateCode p_state_code, int p_row_transform, int p_col_transform);
    
    void LockPiece();
    void NextPiece();
    void InitColorMap();
};

#endif