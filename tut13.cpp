#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<fstream>
#include<string>

SDL_Texture *LoadTexture(std::string filePath, SDL_Renderer *renderTarget)
{
	SDL_Texture *texture = nullptr;
	SDL_Surface *surface = IMG_Load(filePath.c_str());
	if(surface == NULL)
		std::cout << "Could not load the image at: " << filePath << ": " << SDL_GetError() << std::endl;
	else
	{
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		SDL_FreeSurface(surface);
	}

	return texture;
}

void SwitchFrame(SDL_Rect &rect, int frameWidth, int imageWidth)
{
	rect.x += frameWidth; 
	if(rect.x == imageWidth)
		rect.x = 0; 
}

int main(int argc, char *argv[])
{
	// Initializing and loading variables
	SDL_Window *window = nullptr;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("SDL CodingMadeEasy Series", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) & imgFlags))
		std::cout << "Error: " << IMG_GetError() << std::endl;

	SDL_Renderer *renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Texture *texture = LoadTexture("player.png", renderTarget);

	SDL_Rect drawingRect; 
	drawingRect.x = drawingRect.y = 0; 
	drawingRect.w = 40; 
	drawingRect.h = 40;

	bool isRunning = true;
	SDL_Event ev;

	while (isRunning)
	{
		while (SDL_PollEvent(&ev) != 0)
		{
			// Getting the quit and the keyboard events
			if (ev.type == SDL_QUIT)
				isRunning = false;
		}

		SDL_RenderClear(renderTarget); 
		SDL_RenderCopy(renderTarget, texture, &drawingRect, NULL);
		SDL_RenderPresent(renderTarget);

		SDL_UpdateWindowSurface(window);
	}

	// Freeing the memory
	SDL_DestroyTexture(texture); 
	SDL_DestroyRenderer(renderTarget);
	SDL_DestroyWindow(window);

	window = nullptr;
	texture = nullptr; 
	renderTarget = nullptr;

	SDL_Quit();

	return 0;
}
