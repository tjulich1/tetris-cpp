#ifndef RENDER_BOX_HPP
#define RENDER_BOX_HPP

#include <SDL.h>
#include <map>

class RenderBox {
  public: 
    RenderBox(SDL_Rect &p_bounds);  
    virtual void Render(SDL_Renderer* p_renderer, std::map<char, SDL_Color>* p_colors) = 0;
    
  protected:
    SDL_Rect bounds_;
};

#endif