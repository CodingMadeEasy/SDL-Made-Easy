#include<SDL.h>
#include<iostream>
#include<string>

int main(int argc, char *argv[])
{
	// Initializing and loading variables
	SDL_Window *window = nullptr;

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("SDL CodingMadeEasy Series", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

	bool isRunning = true; 
	SDL_Event ev;

	std::string text = ""; 
	SDL_StartTextInput();

	while(isRunning)
	{
		while(SDL_PollEvent(&ev) != 0)
		{
			// Getting the quit and the keyboard events
			if(ev.type == SDL_QUIT)
				isRunning = false;
			else if(ev.type == SDL_TEXTINPUT || ev.type == SDL_KEYDOWN)
			{
				system("cls");
				if(ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_BACKSPACE && text.length() > 0)
					text = text.substr(0, text.length() - 1);
				else if(ev.type == SDL_TEXTINPUT)
					text += ev.text.text;
				
				std::cout << text << std::endl;
			}
		}

		SDL_UpdateWindowSurface(window);
	}

	SDL_StopTextInput();

	window = nullptr;

	SDL_Quit();

	return 0;
}
