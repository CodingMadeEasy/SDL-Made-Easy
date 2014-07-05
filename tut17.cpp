#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<iostream>

SDL_Texture *LoadTexture(std::string filePath, SDL_Renderer *renderTarget)
{
	SDL_Texture *texture = nullptr; 
	SDL_Surface *surface = IMG_Load(filePath.c_str());
	if(surface == NULL) 
		std::cout << "Error" << std::endl; 
	else 
	{
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
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
	SDL_Rect playerRect;
	SDL_Rect playerPosition; 
	playerPosition.x = playerPosition.y = 0; 
	playerPosition.w = playerPosition.h = 32;
	int frameWidth, frameHeight; 
	int textureWidth, textureHeight;
	float frameTime = 0;
	int prevTime = 0; 
	int currentTime = 0; 
	float deltaTime = 0;
	float moveSpeed = 200.0f;
	const Uint8 *keyState;

	SDL_Init(SDL_INIT_VIDEO);
	if(TTF_Init() < 0)
		std::cout << "Error: " << TTF_GetError() << std::endl;

	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if(!(IMG_Init(imgFlags) & imgFlags))
		std::cout << "Error: " << IMG_GetError() << std::endl;

	window = SDL_CreateWindow("SDL CodingMadeEasy Series", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	currentImage = LoadTexture("image.png", renderTarget);

	SDL_QueryTexture(currentImage, NULL, NULL, &textureWidth, &textureHeight);

	frameWidth = textureWidth / 3;
	frameHeight = textureHeight / 4;

	playerRect.x = playerRect.y = 0; 
	playerRect.w = frameWidth; 
	playerRect.h = frameHeight;

	TTF_Font *font = TTF_OpenFont("Stiff Staff.otf", 20);
	SDL_Color color = { 0, 255, 0, 255 };
	SDL_Surface *textSurface = TTF_RenderText_Solid(font, "CodingMadeEasy SDL Series!", color);
	SDL_Texture *text = SDL_CreateTextureFromSurface(renderTarget, textSurface);
	SDL_Rect textRect;
	textRect.x = textRect.y = 0;

	SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);

	SDL_FreeSurface(textSurface);
	textSurface = nullptr;

	bool isRunning = true; 
	SDL_Event ev;

	while(isRunning)
	{
		prevTime = currentTime; 
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - prevTime) / 1000.0f;
		while(SDL_PollEvent(&ev) != 0)
		{
			// Getting the events
			if(ev.type == SDL_QUIT)
				isRunning = false;
		}

		keyState = SDL_GetKeyboardState(NULL);
		if(keyState[SDL_SCANCODE_RIGHT])
			playerPosition.x += moveSpeed * deltaTime;
		else if(keyState[SDL_SCANCODE_LEFT])
			playerPosition.x -= moveSpeed * deltaTime;

		frameTime += deltaTime;

		if(frameTime >= 0.25f)
		{
			frameTime = 0;
			playerRect.x += frameWidth;
			if(playerRect.x >= textureWidth)
				playerRect.x = 0;
		}

		SDL_RenderClear(renderTarget);
		SDL_RenderCopy(renderTarget, currentImage, &playerRect, &playerPosition);
		SDL_RenderCopy(renderTarget, text, NULL, &textRect);
		SDL_RenderPresent(renderTarget);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyTexture(currentImage);
	SDL_DestroyTexture(text); 
	SDL_DestroyRenderer(renderTarget);
	TTF_CloseFont(font);
	window = nullptr;
	currentImage = nullptr;
	renderTarget = nullptr;
	text = nullptr;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	return 0;
}
