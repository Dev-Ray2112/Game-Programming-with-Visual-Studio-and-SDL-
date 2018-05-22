#include <stdio.h>
#include <SDL.h>
using namespace std;

SDL_Surface* background = NULL;
SDL_Surface* sprite = NULL;
SDL_Surface* backbuffer = NULL;

bool ProgramIsRunning();
bool LoadImages();
void FreeImages();

int main(int argc, char* args[])
{

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL failed to initialize!\n");
		SDL_Quit();
		return 0;
	}

	backbuffer = SDL_SetVideoMode(1200, 1000, 32, SDL_SWSURFACE);
	SDL_WM_SetCaption("Ray Martin", NULL);

	if (!LoadImages())
	{
		printf("Images failed to load!\n");
		FreeImages();
		SDL_Quit();

		return 0;
	}

	SDL_BlitSurface(background, NULL, backbuffer, NULL);

	while (ProgramIsRunning())
	{
		SDL_Rect spritePos;
		spritePos.x = rand() % 800;
		spritePos.y = rand() % 600;

		SDL_BlitSurface(sprite, NULL, backbuffer, &spritePos);

		SDL_Flip(backbuffer);

		SDL_Delay(100);
	}


	SDL_Quit();

	return 1;
}

bool ProgramIsRunning()
{
	SDL_Event event;

	bool running = true;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			running = false;
	}

	return running;
}

bool LoadImages()
{
	background = SDL_LoadBMP("graphics/background.bmp");

	if (background == NULL)
		return false;

	sprite = SDL_LoadBMP("graphics/sprite.bmp");

	if (sprite == NULL)
		return false;

	return true;
}

void FreeImages()
{
	if (background != NULL)
	{
		SDL_FreeSurface(background);
		background = NULL;
	}

	if (sprite != NULL)
	{
		SDL_FreeSurface(sprite);
		sprite = NULL;
	}
}