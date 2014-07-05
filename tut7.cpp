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


	// Error checking

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);

	std::cout << SDL_NumJoysticks() << std::endl;
	SDL_Joystick *joystick = SDL_JoystickOpen(0);
	if (joystick == NULL)
		std::cout << "Unable to open Gamepad " << SDL_GetError() << std::endl;
	else
	{
		std::cout << "Name: " << SDL_JoystickName(joystick) << std::endl;
		std::cout << "Num Axes: " << SDL_JoystickNumAxes(joystick) << std::endl;
		std::cout << "Num Buttons: " << SDL_JoystickNumButtons(joystick) << std::endl;
		std::cout << "Num Track balls: " << SDL_JoystickNumBalls(joystick) << std::endl;
		std::cout << "Num Hats: " << SDL_JoystickNumHats(joystick) << std::endl;
	}

	window = SDL_CreateWindow("SDL CodingMadeEasy Series", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	windowSurface = SDL_GetWindowSurface(window);

	image1 = SDL_LoadBMP("test.bmp");
	image2 = SDL_LoadBMP("test1.bmp");
	image3 = SDL_LoadBMP("test2.bmp");

	currentImage = image1;

	bool isRunning = true;
	SDL_Event ev;

	while (isRunning)
	{
		while (SDL_PollEvent(&ev) != 0)
		{
			// Getting the quit and the keyboard events
			if (ev.type == SDL_QUIT)
				isRunning = false;
			else if (ev.type == SDL_JOYAXISMOTION)
			{
				if (ev.jaxis.which == 1)
				{
					//std::cout << ev.jaxis.value << std::endl;
					if (ev.jaxis.axis == 5)
					{
						std::cout << ev.jaxis.value << std::endl;
						if (ev.jaxis.value < -8000)
							currentImage = image2;
						else if (ev.jaxis.value > 8000)
							currentImage = image3;
					}
				}
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

	SDL_JoystickClose(joystick);

	joystick = nullptr;

	image1 = image2 = image3 = windowSurface = nullptr;
	window = nullptr;

	SDL_Quit();

	return 0;
}
