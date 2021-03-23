#include "score_box.hpp"
#include <string>
#include <iostream>

ScoreBox::ScoreBox(SDL_Rect p_bounds) : RenderBox(p_bounds), score_(0) {
  font_ = TTF_OpenFont("OpenSans-Regular.ttf", 12);
}

void ScoreBox::Render(SDL_Renderer* p_renderer, std::map<char, SDL_Color>* p_colors) {
  std::string score_text = "Score: " + (std::to_string(score_));
  SDL_Surface* surface_message = TTF_RenderText_Solid(font_, score_text.c_str(), {0,0,0});
  SDL_Texture* score_message = SDL_CreateTextureFromSurface(p_renderer, surface_message);
  SDL_Rect dest_rect{
    bounds_.x, bounds_.y + bounds_.h / 3, bounds_.w, bounds_.h/3
  };
  SDL_RenderCopy(p_renderer, score_message, NULL, &dest_rect);
  SDL_FreeSurface(surface_message);
  SDL_DestroyTexture(score_message);
}

void ScoreBox::UpdateScore(int p_new_score) {
  score_ = p_new_score;
}

ScoreBox::~ScoreBox() {
  TTF_CloseFont(font_);
}