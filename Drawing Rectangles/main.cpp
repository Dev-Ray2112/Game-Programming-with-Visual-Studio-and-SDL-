#include <SDL.h>
#include <cstdlib>

SDL_Surface* Backbuffer = NULL;

void DrawRect(SDL_Surface* surface, int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b);
void FillRect(SDL_Surface* surface, int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b);
bool ProgramIsRunning();

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Failed to initialize SDL!\n");
		return 0;
	}

	Backbuffer = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);

	SDL_WM_SetCaption("Drawing Rectangles", NULL);

	while (ProgramIsRunning())
	{
		DrawRect(Backbuffer, rand() % 800, rand() % 600, rand() % 200, rand() % 200, rand() % 255, rand() % 255, rand() % 255);
		FillRect(Backbuffer, rand() % 800, rand() % 600, rand() % 200, rand() % 200, rand() % 255, rand() % 255, rand() % 255);

		SDL_Delay(20);
		SDL_Flip(Backbuffer);
	}

	SDL_Quit();

	return 0;
}

void DrawRect(SDL_Surface* surface, int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b)
{
	FillRect(surface, x, y, width, 1, r, g, b);
	FillRect(surface, x, y + height - 1, width, 1, r, g, b);
	FillRect(surface, x, y, 1, height, r, g, b);
	FillRect(surface, x + width - 1, y, 1, height, r, g, b);
}

void FillRect(SDL_Surface* surface, int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b)
{
	Uint32 color;

	color = SDL_MapRGB(surface->format, r, g, b);

	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;

	SDL_FillRect(surface, &rect, color);
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