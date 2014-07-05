#include<SDL.h>
#include<iostream>

SDL_Surface *OptimizedSurface(std::string filePath, SDL_Surface *windowSurface)
{
	SDL_Surface *optimizedSurface = nullptr; 
	SDL_Surface *surface = SDL_LoadBMP(filePath.c_str());
	if(surface == NULL) 
		std::cout << "Error" << std::endl; 
	else 
	{
		optimizedSurface = SDL_ConvertSurface(surface, windowSurface->format, 0);
		if(optimizedSurface == NULL)
			std::cout << "Error" << std::endl;
	}

	SDL_FreeSurface(surface);

	return optimizedSurface;
}

int main(int argc, char *argv[])
{
	// Initializing and loading variables
	SDL_Window *window = nullptr;
	SDL_Surface *windowSurface = nullptr; 
	SDL_Surface *currentImage = nullptr;

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("SDL CodingMadeEasy Series", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	windowSurface = SDL_GetWindowSurface(window); 
	currentImage = OptimizedSurface("testsmall.bmp", windowSurface);

	SDL_Rect drawingRect; 
	drawingRect.x = drawingRect.y = 0; 
	drawingRect.w = 640; 
	drawingRect.h = 480;

	bool isRunning = true; 
	SDL_Event ev;

	while(isRunning)
	{
		while(SDL_PollEvent(&ev) != 0)
		{
			// Getting the events
			if(ev.type == SDL_QUIT)
				isRunning = false;
		}

		SDL_BlitScaled(currentImage, NULL, windowSurface, &drawingRect);
		SDL_UpdateWindowSurface(window);
	}

	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_FreeSurface(currentImage);
	currentImage = windowSurface = nullptr;

	SDL_Quit();

	return 0;
}
