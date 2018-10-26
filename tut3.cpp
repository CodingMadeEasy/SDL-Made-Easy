#include<SDL.h> // The main Header file of SDL library
#include<iostream> // input output stream header file

int main(int argc, char *argv[])
{
	SDL_Window *window = nullptr; // Allocating space for Display Window.
	SDL_Surface *windowSurface = nullptr; // Allocating space for Window Surface
	SDL_Surface *image = nullptr; // Allocating space for another Surface named image

	if(SDL_Init(SDL_INIT_VIDEO) < 0) // Initializing SDL and checking if it is initialized
		std::cout << "Video Initialization Error: " << SDL_GetError() << std::endl; // If Initializing failed then display erroror

	window = SDL_CreateWindow("SDL Tutorial Series", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN); // Creating Display Window with following attributes
	if(window == NULL)
		std::cout << "Window creation Error: " << SDL_GetError() << std::endl; // If the window wasn't created then the default value will be NULL, ckeck the line no. 6
	else 
	{
		windowSurface = SDL_GetWindowSurface(window); // specifing from which window to get surface Displayed.
		image = SDL_LoadBMP("test.bmp"); // painting "test.bmp" to image Surface
		if(image != NULL) // checking if image was successfully loaded
		{
			SDL_BlitSurface(image, NULL, windowSurface, NULL); // Draw from image Surface to windowSurface
			SDL_UpdateWindowSurface(window); //Redrawing everything on the Display Window
			SDL_Delay(2000); // Wait for two seconds
		}
	}

	SDL_FreeSurface(image); // Deallocating resources acquired by Surface image.
	image = nullptr; // assigning null pointer to avoid dangling pointer
	SDL_DestroyWindow(window); // Deallocating resources acquired by Display window.
	window = nullptr; // assigning null pointer to avoid dangling pointer

	SDL_Quit(); // Deallocating the Initialized SDL.

	return 0;
}
