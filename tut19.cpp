#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<iostream>

SDL_Texture *LoadTexture(std::string filePath, SDL_Renderer *renderTarget)
{
	SDL_Texture *texture = nullptr; 
	SDL_Surface *surface = IMG_Load(filePath.c_str());
	if(surface == NULL) 
		std::cout << "Error" << std::endl; 
	else 
	{
		//SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 0));
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		SDL_SetTextureColorMod(texture, 128, 255, 255);
		if(texture == NULL)
			std::cout << "Error" << std::endl;
	}

	SDL_FreeSurface(surface);

	return texture;
}

int main(int argc, char *argv[])
{
	// Initializing and loading variables
	SDL_Window *window = nullptr;
	SDL_Texture *currentImage = nullptr;
	SDL_Renderer *renderTarget = nullptr;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	window = SDL_CreateWindow("SDL CodingMadeEasy Series", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "Error: " << Mix_GetError() << std::endl;

	Mix_Music *bgm = Mix_LoadMUS("bgm.mp3"); 
	Mix_Chunk *soundEffect = Mix_LoadWAV("waterdrop.wav");

	bool isRunning = true; 
	SDL_Event ev;

	while(isRunning)
	{
		while(SDL_PollEvent(&ev) != 0)
		{
			// Getting the events
			if(ev.type == SDL_QUIT)
				isRunning = false;
			else if(ev.type == SDL_KEYDOWN)
			{
				switch(ev.key.keysym.sym)
				{
				case SDLK_p: 
					if(!Mix_PlayingMusic())
						Mix_PlayMusic(bgm, -1);
					else if(Mix_PausedMusic())
						Mix_ResumeMusic();
					else 
						Mix_PauseMusic();
					break;
				case SDLK_s:
					Mix_HaltMusic();
					break;
				case SDLK_1: 
					Mix_PlayChannel(1, soundEffect, 2);
					break;
				}
			}
		}

		SDL_RenderClear(renderTarget);
		SDL_RenderCopy(renderTarget, currentImage, NULL, NULL);
		//SDL_RenderCopy(renderTarget, text, NULL, &textRect);
		SDL_RenderPresent(renderTarget);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyTexture(currentImage); 
	SDL_DestroyRenderer(renderTarget);

	Mix_FreeChunk(soundEffect); 
	Mix_FreeMusic(bgm); 

	bgm = nullptr; 
	soundEffect = nullptr;

	window = nullptr;
	currentImage = nullptr;
	renderTarget = nullptr;

	Mix_Quit();
	SDL_Quit();

	return 0;
}
