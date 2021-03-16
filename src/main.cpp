// Trent Julich ~ 03/02/2021

#include "tetris_game.hpp"
#include "tetris_input.hpp"
#include "tetris_events.hpp"

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

//Screen dimension constants
const int kWindowWidth = 300;
const int kWindowHeight = 500;

TetrisGame* current_game;

unsigned int Tick(unsigned int p_interval, void* p_params) {
  std::cout << "Game Tick" << std::endl;
  SDL_Event drop_event;
  SDL_UserEvent drop_user_event;
  drop_user_event.type = SDL_USEREVENT;
  drop_user_event.code = DROP;
  drop_event.type = SDL_USEREVENT;
  drop_event.user = drop_user_event;

  SDL_PushEvent(&drop_event);

  return p_interval;
}

int main( int argc, char* args[] )
{
	SDL_Window* window = NULL;
	
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0 ) {
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
	}
	else {
		std::cout << "Not even here" << std::endl;
		// Check if initializing SDL_ttf fails.
		if (TTF_Init() == -1) {
			std::cout << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
		} else {
			std::cout << "Here?" << std::endl;
			window = SDL_CreateWindow( "Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		  kWindowWidth, kWindowHeight, SDL_WINDOW_SHOWN );

			if (window == NULL) {
				std::cout << "Window could not be created: " <<  SDL_GetError() << std::endl;
			} else {
				// Renderer for graphics.
				SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

				SDL_TimerID timer = SDL_AddTimer(3000, Tick, NULL);

				// Create new instance of game, using renderer.
		  	current_game = new TetrisGame(renderer);

				TetrisInput user_input(current_game);

				bool quit = false;
				while (!quit) {
					quit = user_input.HandleInput();
					current_game->Render();	
				}

				// Clean up current game
				delete current_game;
				current_game = nullptr;	

				SDL_DestroyRenderer(renderer);
			}
		
		}
	}
	SDL_DestroyWindow( window );
	SDL_Quit();
	return 0;
}