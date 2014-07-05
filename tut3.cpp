#include<SDL.h>
#include<iostream>

int main(int argc, char *argv[])
{
	SDL_Window *window = nullptr;
	SDL_Surface *windowSurface = nullptr;
	SDL_Surface *image = nullptr; 

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		std::cout << "Video Initialization Error: " << SDL_GetError() << std::endl; 

	window = SDL_CreateWindow("SDL Tutorial Series", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	if(window == NULL)
		std::cout << "Window creation Error: " << SDL_GetError() << std::endl; 
	else 
	{
		windowSurface = SDL_GetWindowSurface(window);
		image = SDL_LoadBMP("test.bmp");
		if(image != NULL)
		{
			SDL_BlitSurface(image, NULL, windowSurface, NULL);
			SDL_UpdateWindowSurface(window); 
			SDL_Delay(2000);
		}
	}

	SDL_FreeSurface(image);
	image = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_Quit();

	return 0;
}