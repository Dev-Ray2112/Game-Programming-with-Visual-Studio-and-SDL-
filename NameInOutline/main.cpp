#include <SDL.h>
#include <SDL_ttf.h>

SDL_Surface* Backbuffer = NULL;
TTF_Font* Font = NULL;

void DrawOutlineText(SDL_Surface* surface, char* string, int x, int y, TTF_Font* font, Uint8 r, Uint8 g, Uint8 b);
bool ProgramIsRunning();

int main(int argc, char* args[])
{

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Failed to initialize SDL!\n");
		return 0;
	}

	Backbuffer = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);

	if (TTF_Init() == -1)
		return 0;

	Font = TTF_OpenFont("fonts/Alfphabet.ttf", 24);

	if (Font == NULL)
	{
		printf("Failed to load font!\n");
		TTF_CloseFont(Font);
		TTF_Quit();
		SDL_Quit();

		return 0;
	}

	SDL_WM_SetCaption("Outline Font", NULL);

	int counter = 0;

	while (ProgramIsRunning())
	{
		SDL_FillRect(Backbuffer, NULL, 0);

		counter++;
		if (counter > 1000)
			counter = 0;

		char buffer[64];
		sprintf_s(buffer, "Ray Martin %d", counter);

		DrawOutlineText(Backbuffer, "Ray Martin", 100, 100, Font, 255, 0, 0);
		DrawOutlineText(Backbuffer, "Ray Martin", 100, 150, Font, 0, 255, 0);
		DrawOutlineText(Backbuffer, buffer, 100, 200, Font, 0, 0, 255);

		SDL_Delay(20);
		SDL_Flip(Backbuffer);
	}

	TTF_CloseFont(Font);
	TTF_Quit();
	SDL_Quit();

	return 0;
}

void DrawOutlineText(SDL_Surface* surface, char* string, int x, int y, TTF_Font* font, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Surface* renderedText = NULL;

	SDL_Color color;

	color.r = r;
	color.g = g;
	color.b = b;

	renderedText = TTF_RenderText_Solid(font, string, color);

	SDL_Rect pos;

	pos.x = x;
	pos.y = y;

	SDL_BlitSurface(renderedText, NULL, surface, &pos);
	SDL_FreeSurface(renderedText);
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