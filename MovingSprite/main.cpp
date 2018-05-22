#include <SDL.h>

SDL_Surface* Background = NULL;
SDL_Surface* SpriteImage = NULL;
SDL_Surface* Backbuffer = NULL;

SDL_Rect SpritePos;

bool LoadFiles();
void FreeFiles();
bool ProgramIsRunning();

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Failed to initialize SDL!\n");
		return 0;
	}

	Backbuffer = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);

	SDL_WM_SetCaption("Moving Image", NULL);

	if (!LoadFiles())
	{
		printf("Failed to load files!\n");
		FreeFiles();
		SDL_Quit();

		return 0;
	}

	SpritePos.x = 0;
	SpritePos.y = 250;

	while (ProgramIsRunning())
	{
		SpritePos.x += 5;

		if (SpritePos.x > 800)
			SpritePos.x = -200;

		SDL_BlitSurface(Background, NULL, Backbuffer, NULL);
		SDL_BlitSurface(SpriteImage, NULL, Backbuffer, &SpritePos);

		SDL_Delay(20);
		SDL_Flip(Backbuffer);
	}

	FreeFiles();

	SDL_Quit();

	return 0;
}

bool LoadFiles()
{
	Background = SDL_LoadBMP("graphics/background.bmp");
	if (Background == NULL)
		return false;

	SpriteImage = SDL_LoadBMP("graphics/spaceship.bmp");

	if (SpriteImage == NULL)
		return false;

	return true;
}

void FreeFiles()
{
	SDL_FreeSurface(Background);
	SDL_FreeSurface(SpriteImage);
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