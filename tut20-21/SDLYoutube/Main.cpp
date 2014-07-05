#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include"Player.h"

int main(int argc, char *argv[])
{
	// Initializing and loading variables
	SDL_Window *window = nullptr;
	SDL_Renderer *renderTarget = nullptr;
	int currentTime = 0; 
	int prevTime = 0; 
	float delta = 0.0f;
	const Uint8 *keyState;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("SDL CodingMadeEasy Series", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	Player player1(renderTarget, "image.png", 0, 0, 3, 4);
	Player player2(renderTarget, "image.png", 500, 300, 3, 4);

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

		player1.IntersectsWith(player2);

		SDL_RenderClear(renderTarget);
		//SDL_RenderCopy(renderTarget, text, NULL, &textRect);
		player1.Draw(renderTarget); 
		player2.Draw(renderTarget);
		SDL_RenderPresent(renderTarget);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderTarget);

	window = nullptr;
	renderTarget = nullptr;

	IMG_Quit();
	SDL_Quit();

	return 0;
}
