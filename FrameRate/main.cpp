#include <SDL.h>

const int FPS = 50;
const int FRAME_DELAY = 1000 / FPS;

SDL_Surface* Background = NULL;
SDL_Surface* SpriteImage = NULL;
SDL_Surface* Backbuffer = NULL;

int SpriteFrame = 0;
int FrameCounter = 0;

const int MaxSpriteFrame = 11;
const int FrameDelay = 2;

int BackgroundX = 0;

SDL_Surface* LoadImage(char* fileName);
bool LoadFiles();
void FreeFiles();
void DrawImage(SDL_Surface* image, SDL_Surface* destSurface, int x, int y);
void DrawImageFrame(SDL_Surface* image, SDL_Surface* destSurface, int x, int y, int width, int height, int frame);
bool ProgramIsRunning();

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Failed to initialize SDL!\n");
		return 0;
	}

	Backbuffer = SDL_SetVideoMode(1200, 800, 32, SDL_SWSURFACE);

	SDL_WM_SetCaption("Frame Rate Regulation", NULL);

	if (!LoadFiles())
	{
		printf("Failed to load all files!\n");
		FreeFiles();
		SDL_Quit();

		return 0;
	}

	while (ProgramIsRunning())
	{
		int frameStart = SDL_GetTicks();

		//Update's the sprites frame
		FrameCounter++;

		if (FrameCounter > FrameDelay)
		{
			FrameCounter = 0;
			SpriteFrame++;
		}

		if (SpriteFrame > MaxSpriteFrame)
			SpriteFrame = 0;

		//Update's Background scrolling
		BackgroundX -= 6;
		if (BackgroundX <= -1200)
			BackgroundX = 0;

		//Render the scene
		DrawImage(Background, Backbuffer, BackgroundX, 0);
		DrawImage(Background, Backbuffer, BackgroundX + 800, 0);
		DrawImageFrame(SpriteImage, Backbuffer, 350, 250, 150, 120, SpriteFrame);


		int frameTime = SDL_GetTicks() - frameStart;

		if (frameTime < FRAME_DELAY)
			SDL_Delay(FRAME_DELAY - frameTime);

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

	SpriteImage = LoadImage("graphics/demon.bmp");

	if (SpriteImage == NULL)
		return false;

	return true;
}

void FreeFiles()
{
	SDL_FreeSurface(Background);
	SDL_FreeSurface(SpriteImage);
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