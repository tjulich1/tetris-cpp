#ifndef SCORE_BOX_HPP
#define SCORE_BOX_HPP

#include "render_box.hpp"
#include <SDL_ttf.h>

class ScoreBox : RenderBox {
  public:
    ScoreBox(SDL_Rect p_bounds);
    ~ScoreBox();
    void Render(SDL_Renderer* p_renderer, std::map<char, SDL_Color>* p_colors) override;
    void UpdateScore(int p_new_score);
  private: 
    int score_;
    TTF_Font* font_;
};

#endif