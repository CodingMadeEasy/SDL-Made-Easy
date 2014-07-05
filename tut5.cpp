#include<SDL.h>
#include<iostream>

int main(int argc, char *argv[])
{
	// Creating and initializing variables
	SDL_Window *window = nullptr;
	SDL_Surface *windowSurface = nullptr;
	SDL_Surface *image1 = nullptr; 
	SDL_Surface *image2 = nullptr; 
	SDL_Surface *image3 = nullptr;
	SDL_Surface *currentImage = nullptr;
	SDL_Init(SDL_INIT_VIDEO);
	
	window = SDL_CreateWindow("SDL CodingMadeEasy Series", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	windowSurface = SDL_GetWindowSurface(window);

	image1 = SDL_LoadBMP("test.bmp"); 
	image2 = SDL_LoadBMP("test1.bmp"); 
	image3 = SDL_LoadBMP("test2.bmp"); 

	currentImage = image1;

	bool isRunning = true; 
	SDL_Event ev;

	while(isRunning)
	{
		while(SDL_PollEvent(&ev) != 0)
		{
			// Getting the quit and the keyboard events
			if(ev.type == SDL_QUIT)
				isRunning = false;
			else if(ev.type == SDL_KEYUP)
			{
				switch(ev.key.keysym.sym)
				{
				case SDLK_1:
					currentImage = image1; 
					break; 
				case SDLK_2: 
					currentImage = image2; 
					break; 
				case SDLK_3: 
					currentImage = image3; 
					break;
				}
			}
		}

		// Drawing the current image to the window
		SDL_BlitSurface(currentImage, NULL, windowSurface, NULL);
		SDL_UpdateWindowSurface(window);
	}

	// Freeing the memory
	SDL_FreeSurface(image1); 
	SDL_FreeSurface(image2); 
	SDL_FreeSurface(image3);
	SDL_DestroyWindow(window);

	image1 = image2 = image3 = windowSurface = nullptr;
	window = nullptr;

	SDL_Quit();

	return 0;
}
