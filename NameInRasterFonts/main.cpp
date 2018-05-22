#include <SDL.h>

SDL_Surface* Background = NULL;
SDL_Surface* FontImage = NULL;
SDL_Surface* Backbuffer = NULL;

const int charSize = 16;

SDL_Surface* LoadImage(char* fileName);
bool LoadFiles();
void FreeFiles();
void DrawImage(SDL_Surface* image, SDL_Surface* destSurface, int x, int y);
void DrawImageFrame(SDL_Surface* image, SDL_Surface* destSurface, int x, int y, int width, int height, int frame);
void DrawRasterText(SDL_Surface* surface, SDL_Surface* destSurface, char string[], int x, int y, int charSize);
bool ProgramIsRunning();

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Failed to initialize SDL!\n");
		return 0;
	}

	Backbuffer = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);

	SDL_WM_SetCaption("Raster Fonts", NULL);

	if (!LoadFiles())
	{
		printf("Failed to load all files!\n");
		FreeFiles();
		SDL_Quit();

		return 0;
	}

	while (ProgramIsRunning())
	{
		DrawImage(Background, Backbuffer, 0, 0);
		DrawRasterText(FontImage, Backbuffer, "Ray Martin", 200, 216, charSize);
		

		SDL_Delay(20);
		SDL_Flip(Backbuffer);
	}

	FreeFiles();

	SDL_Quit();

	return 0;
}

SDL_Surface* LoadImage(char* fileName)
{
	SDL_Surface* imageLoaded = NULL;
	SDL_Surface* processedImage = NULL;

	imageLoaded = SDL_LoadBMP(fileName);

	if (imageLoaded != NULL)
	{
		processedImage = SDL_DisplayFormat(imageLoaded);
		SDL_FreeSurface(imageLoaded);

		if (processedImage != NULL)
		{
			Uint32 colorKey = SDL_MapRGB(processedImage->format, 0xFF, 0, 0xFF);
			SDL_SetColorKey(processedImage, SDL_SRCCOLORKEY, colorKey);
		}

	}

	return processedImage;
}

bool LoadFiles()
{
	Background = LoadImage("graphics/background.bmp");

	if (Background == NULL)
		return false;

	FontImage = LoadImage("graphics/blocky_font.bmp");

	if (FontImage == NULL)
		return false;

	return true;
}

void FreeFiles()
{
	SDL_FreeSurface(FontImage);
	SDL_FreeSurface(Background);
}

void DrawImage(SDL_Surface* image, SDL_Surface* destSurface, int x, int y)
{
	SDL_Rect destRect;
	destRect.x = x;
	destRect.y = y;

	SDL_BlitSurface(image, NULL, destSurface, &destRect);
}

void DrawImageFrame(SDL_Surface* image, SDL_Surface* destSurface, int x, int y, int width, int height, int frame)
{
	//Draws a specific frame from an image
	SDL_Rect destRect;
	destRect.x = x;
	destRect.y = y;

	int collumns = image->w / width;

	SDL_Rect sourceRect;
	sourceRect.y = (frame / collumns)*height;
	sourceRect.x = (frame%collumns)*width;
	sourceRect.w = width;
	sourceRect.h = height;

	SDL_BlitSurface(image, &sourceRect, destSurface, &destRect);
}

void DrawRasterText(SDL_Surface* surface, SDL_Surface* destSurface, char string[], int x, int y, int charSize)
{
	for (int i = 0; i < strlen(string); i++)
		DrawImageFrame(surface, destSurface, x + i*charSize, y, charSize, charSize, string[i] - 32);
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