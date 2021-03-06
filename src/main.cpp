// Trent Julich ~ 03/02/2021

#include "tetris_game.hpp"
#include "user_input.hpp"

#include <iostream>
#include <SDL.h>

//Screen dimension constants
const int kWindowWidth = 200;
const int kWindowHeight = 300;

TetrisGame* current_game;

int main( int argc, char* args[] )
{
	SDL_Window* window = NULL;
	
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0 ) {
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
	}
	else {
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		  kWindowWidth, kWindowHeight, SDL_WINDOW_SHOWN );

		if (window == NULL) {
			std::cout << "Window could not be created: " <<  SDL_GetError() << std::endl;
		} else {
			// Renderer for graphics.
			SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			// Create new instance of game, using renderer.
		  current_game = new TetrisGame(renderer);

			// This call starts the game loop, and only returns when user ends game.
			current_game->StartGame();

			// Clean up current game
			delete current_game;
			current_game = nullptr;	

			SDL_DestroyRenderer(renderer);
		}
	}
	SDL_DestroyWindow( window );
	SDL_Quit();
	return 0;
}