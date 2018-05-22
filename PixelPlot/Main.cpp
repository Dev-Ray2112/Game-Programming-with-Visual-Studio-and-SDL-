#include <SDL.h>
#include <cstdlib>


SDL_Surface* Backbuffer = NULL;

bool ProgramIsRunning();
void DrawPixel(SDL_Surface *surface, int x, int y, Uint8 r, Uint8 g, Uint8 b);

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Failed to initialize SDL!\n");
		return 0;
	}

	Backbuffer = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);

	SDL_WM_SetCaption("Pixel Plot", NULL);

	while (ProgramIsRunning())
	{

		for (int i = 0; i < 100; i++)
		{
			DrawPixel(Backbuffer, rand() % 800, rand() % 600, rand() % 255, rand() % 255, rand() % 255);
		}

		SDL_Delay(20);
		SDL_Flip(Backbuffer);
	}

	SDL_Quit();

	return 0;
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

void DrawPixel(SDL_Surface *surface, int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
	if (SDL_MUSTLOCK(surface))
	{
		if (SDL_LockSurface(surface) < 0)
			return;
	}

	if (x >= surface->w || x < 0 || y >= surface->h || y < 0)
		return;

	Uint32 *buffer;
	Uint32 color;

	color = SDL_MapRGB(surface->format, r, g, b);

	buffer = (Uint32*)surface->pixels + y*surface->pitch / 4 + x;
	(*buffer) = color;

	if (SDL_MUSTLOCK(surface))
		SDL_UnlockSurface(surface);
}