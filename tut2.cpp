#include<SDL.h>
#include<iostream>

int main(int argc, char *argv[])
{
	SDL_Window *window = nullptr;
	
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		std::cout << "Video Initialization Error: " << SDL_GetError() << std::endl;
	else
	{
		window = SDL_CreateWindow("SDL CodingMadeEasy Series", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
		if(window == NULL)
			std::cout << "Window Creation Error: " << SDL_GetError() << std::endl; 
		else 
		{
			SDL_UpdateWindowSurface(window);
			SDL_Delay(2000);
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
