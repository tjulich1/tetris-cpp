/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include "user_input.hpp"
#include <iostream>

//Screen dimension constants
const int kWindowWidth = 200;
const int kWindowHeight = 300;
const int kDesiredFPS = 60;
const int kTimePerFrame = 1000 / kDesiredFPS;

TetrisGame* current_game;

int main( int argc, char* args[] )
{
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
	}
	else
	{
		//Create window
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		  kWindowWidth, kWindowHeight, SDL_WINDOW_SHOWN );

		if (window == NULL) {
			std::cout << "Window could not be created: " <<  SDL_GetError() << std::endl;
		} else {;

			SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			// Main loop flag
			bool quit = false;

			// Event handler
			SDL_Event e;	

		  current_game = new TetrisGame(renderer);
			
			while (!quit) 
			{
				while (SDL_PollEvent(&e))
				{
					// Exit game if exit command is given.
					if (e.type == SDL_QUIT) 
					{
						quit = true;
					} 
					else 
					{
						handleUserInput(e);
					}
					
				}

				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderClear(renderer);
				current_game->Render();
				SDL_RenderPresent(renderer);
			}	
			delete current_game;
			current_game = 0;	
			SDL_DestroyRenderer(renderer);
		}
	}

	SDL_DestroyWindow( window );
	SDL_Quit();

	return 0;
}