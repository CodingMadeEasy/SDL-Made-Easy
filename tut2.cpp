#include<SDL.h> // The main Header file of SDL library
#include<iostream> // input output stream header file

int main(int argc, char *argv[])
{
	SDL_Window *window = nullptr; // Allocating space for Display Window.
	
	if(SDL_Init(SDL_INIT_VIDEO) < 0) // Initializing SDL and checking if it is initialized
		std::cout << "Video Initialization Error: " << SDL_GetError() << std::endl; // If Initializing failed then display error
	else
	{
		window = SDL_CreateWindow("SDL CodingMadeEasy Series", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN); // Creating Display Window with following attributes
		if(window == NULL)
			std::cout << "Window Creation Error: " << SDL_GetError() << std::endl; // If the window wasn't created then the default value will be NULL, ckeck the line no. 6
		else 
		{
			SDL_UpdateWindowSurface(window); //Redrawing everything on the Display Window
			SDL_Delay(2000); // Wait for two seconds
		}
	}

	SDL_DestroyWindow(window); // Deallocating resources acquired by Display window.
	SDL_Quit(); // Deallocating the Initialized SDL.

	return 0;
}
