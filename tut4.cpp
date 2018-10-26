#include<SDL.h> // The main Header file of SDL library
#include<iostream> // input output stream header file

int main(int argc, char *argv[])
{
	SDL_Window *window = nullptr; // Allocating space for Display Window.
	SDL_Init(SDL_INIT_VIDEO); // Initializing SDL
	
	window = SDL_CreateWindow("SDL CodingMadeEasy Series", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN); // Creating Display Window with following attributes

	bool isRunning = true; // Game loop triger
	SDL_Event ev; // Allocating space for Event ev

	while(isRunning) // main Game loop
	{
		while(SDL_PollEvent(&ev) != 0) // main Event loop, checks if Event ev is empty
		{
			if(ev.type == SDL_QUIT) // if windows is closed
				isRunning = false; // Game loop triger set to false
		}
		SDL_UpdateWindowSurface(window); //Redrawing everything on the Display Window
	}

	SDL_DestroyWindow(window); // Deallocating resources acquired by Display window.
	SDL_Quit(); // Deallocating the Initialized SDL.
	
	return 0;
}
