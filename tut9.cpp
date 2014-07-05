#include<SDL.h>
#include<iostream>

int main(int argc, char *argv[])
{
	// Initializing and loading variables
	SDL_Window *window = nullptr;
	SDL_Surface *windowSurface = nullptr;
	SDL_Surface *image1 = nullptr; 
	SDL_Surface *image2 = nullptr; 
	SDL_Surface *image3 = nullptr;
	SDL_Surface *currentImage = nullptr;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);

	SDL_GameController *controller = nullptr;

	for(int i = 0; i < SDL_NumJoysticks(); i++)
	{
		if(SDL_IsGameController(i))
		{
			controller = SDL_GameControllerOpen(i);
			std::cout << SDL_GameControllerMapping(controller) << std::endl;
			break;
		}
	}

	std::cout << SDL_GameControllerAddMapping("0,X360 Controller,a:b11,b:b10");
	//SDL_GameControllerUpdate(); Updates the controller if you're not in a loop
	//SDL_GameControllerGetStringForButton(SDL_CONTROLLER_BUTTON_A) // Gives you the mapping name for the specified button
	//SDL_GameControllerGetStringForAxis(AXIS_GOES_HERE) // Gives you the mapping name for the specified axis

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
			else if(ev.type == SDL_CONTROLLERBUTTONDOWN)
			{
				if(ev.cbutton.button == SDL_CONTROLLER_BUTTON_A)
					currentImage = image2; 
				else if(ev.cbutton.button == SDL_CONTROLLER_BUTTON_B)
					currentImage = image3;
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

	if(controller != NULL)
		SDL_GameControllerClose(controller); 

	controller = nullptr;

	image1 = image2 = image3 = windowSurface = nullptr;
	window = nullptr;

	SDL_Quit();

	return 0;
}
