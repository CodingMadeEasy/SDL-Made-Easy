#include<SDL.h>
#include<SDL_image.h>
#include<SDL_thread.h>
#include<iostream>
#include"Player.h"

SDL_Texture *LoadTexture (std::string filePath, SDL_Renderer *renderTarget)
{
	SDL_Texture *texture = nullptr;
	SDL_Surface *surface = IMG_Load(filePath.c_str());
	if (surface == NULL)
		std::cout << "Error" << std::endl;
	else
	{
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		if (texture == NULL)
			std::cout << "Error" << std::endl;
	}

	SDL_FreeSurface(surface);

	return texture;
}

int main(int argc, char *argv[])
{
	// Initializing and loading variables
	SDL_Window *window = nullptr;
	SDL_Renderer *renderTarget = nullptr;
	int currentTime = 0; 
	int prevTime = 0; 
	float delta = 0.0f;
	const Uint8 *keyState;
	SDL_Rect camerRect = { 0, 0, 640, 480 };
	int levelWidth, levelHeight;

	SDL_Init(SDL_INIT_VIDEO);
	
	if(IMG_Init(imgFlags) != imgFlags)
		std::cout << "Error: " << IMG_GetError() << std::endl;

	int data = 10;
	window = SDL_CreateWindow("SDL CodingMadeEasy Series", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	Player player1(renderTarget, "image.png", 0, 0, 3, 4);
	Player player2(renderTarget, "image.png", 500, 300, 3, 4);

	SDL_Texture *texture = LoadTexture("rect.png", renderTarget);
	SDL_QueryTexture(texture, NULL, NULL, &levelWidth, &levelHeight);

	bool isRunning = true; 
	SDL_Event ev;

	while(isRunning)
	{
		prevTime = currentTime; 
		currentTime = SDL_GetTicks(); 
		delta = (currentTime - prevTime) / 1000.0f;
		while(SDL_PollEvent(&ev) != 0)
		{
			// Getting the events
			if(ev.type == SDL_QUIT)
				isRunning = false;
		}

		keyState = SDL_GetKeyboardState(NULL);

		player1.Update(delta, keyState); 
		player2.Update(delta, keyState);


		camerRect.x = player1.GetOriginX() - 320; 
		camerRect.y = player1.GetOriginY() - 240;

		if(camerRect.x < 0)
			camerRect.x = 0; 
		if(camerRect.y < 0)
			camerRect.y = 0;

		if(camerRect.x + camerRect.w >= levelWidth)
			camerRect.x = levelWidth - 640; 
		if(camerRect.y + camerRect.h >= levelHeight)
			camerRect.y = levelHeight - 480;


		player1.IntersectsWith(player2);

		SDL_RenderClear(renderTarget);
		SDL_RenderCopy(renderTarget, texture, &camerRect, NULL);
		player1.Draw(renderTarget, camerRect); 
		player2.Draw(renderTarget, camerRect);
		SDL_RenderPresent(renderTarget);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderTarget);
	SDL_DestroyTexture(texture);

	texture = nullptr;

	window = nullptr;
	renderTarget = nullptr;

	IMG_Quit();
	SDL_Quit();

	return 0;
}
