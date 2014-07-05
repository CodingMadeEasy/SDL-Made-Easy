#include<SDL.h>
#include<iostream>

int main(int argc, char *argv[])
{
	SDL_Window *window = nullptr;
	SDL_Init(SDL_INIT_VIDEO);
	
	window = SDL_CreateWindow("SDL CodingMadeEasy Series", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

	bool isRunning = true; 
	SDL_Event ev;

	while(isRunning)
	{
		while(SDL_PollEvent(&ev) != 0)
		{
			if(ev.type == SDL_QUIT)
				isRunning = false;
		}
		SDL_UpdateWindowSurface(window);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
