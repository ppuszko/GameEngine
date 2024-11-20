#include "Sprite.h"
#include <SDL.h>
#include <SDL_image.h>
#include <vector>


Sprite::Sprite()
{
	sHeight = 0;
	sWidth = 0;
	sTexture = NULL;

}

Sprite::~Sprite()
{
	free();
}

void Sprite::free()
{
	if (sTexture != NULL)
	{
		SDL_DestroyTexture(sTexture);
		sTexture = NULL;
		sWidth = 0;
		sHeight = 0;
	}
}

bool Sprite::loadFromFile(std::string path, SDL_Renderer* renderer)
{
	free();

	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL)
	{
		printf("Surface could not be loaded! Error for path: %s\n IMG Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Texture could not be created! Error for path: %s\n IMG Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			sWidth = loadedSurface->w;
			sHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	sTexture = newTexture;
	return sTexture != NULL;
}

void Sprite::clipSpriteSheet(int cols, int rows)
{
	int clipWidth = sWidth / cols;
	int clipHeight = sHeight / rows;
	sWidth = clipWidth;
	sHeight = clipHeight;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			animationClips.push_back({ clipWidth * j,
									clipHeight * i,
									clipWidth,
									clipHeight });
		}
	}
}

void Sprite::render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip, int scale, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	int bufferX{ 0 };
	int bufferY{ 0 };

	SDL_Rect destQuad = { x - bufferX, y+bufferY, sWidth,  sHeight };
	if (clip != NULL)
	{
		destQuad.w = scale*clip->w;
		destQuad.h = scale*clip->h;
		bufferX = (destQuad.w) / 2;
		bufferY = (destQuad.h) / 2;
		destQuad.x -= bufferX;
		destQuad.y += bufferY;
	}

	SDL_RenderCopyEx(renderer, sTexture, clip, &destQuad, angle, center, flip);
}

void Sprite::renderAnimation(int x, int y, SDL_Renderer* renderer, std::vector<SDL_Rect>& clip, int& startingFrame, int scale, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	int bufferX = clip[0].w / 2;
	int bufferY = clip[0].h / 2;


	SDL_Rect destQuad = { 
		x - bufferX,
		y - bufferY,
		clip[0].w*scale, 
		clip[0].h*scale };


	int currentFrame = startingFrame / 4;
	if (currentFrame >= clip.size())
	{
		startingFrame = 0;
		currentFrame = 0;
	}
	SDL_RenderCopyEx(renderer, sTexture, &clip[currentFrame], &destQuad, angle, center, flip);
	startingFrame++;
}

int Sprite::getWidth() const
{
	return sWidth;
}

int Sprite::getHeight() const
{
	return sHeight;
}

std::vector<SDL_Rect> Sprite::getAnimationClips() const
{
	return animationClips;
}

void Sprite::updateDimensions(int width, int height)
{
	sWidth = width;
	sHeight = height;
}

void Sprite::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(sTexture, red, green, blue);
}

void Sprite::setBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(sTexture, blending);
}

void Sprite::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(sTexture, alpha);
}



bool init(SDL_Window*& window, SDL_Renderer*& renderer, int width, int height)
{
	bool success = true;

	window = SDL_CreateWindow("Window name", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else{
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer == NULL)
		{
			printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

			//initilazies SDL_image to use PNG files. If IMG_INIT_PNG's initialization didn't succeed, IMG_INIT(imgFlags) will return 0, which will trigger if condition
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_Image could not be loaded! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			}
		}
	}
	return success;
}

bool loadSpriteSheet(Sprite& spriteTexture, SDL_Renderer* renderer, std::string path )
{
	
	if (!spriteTexture.loadFromFile(path.c_str(), renderer))
	{
		printf("Failed to load sprite sheet texture! \n");
		return false;
	}
	//spriteTexture.setBlendMode(SDL_BLENDMODE_BLEND);
	
	return true;
}

std::vector<SDL_Rect> clipSpriteSheet(Sprite& spriteTexture, int cols, int rows)
{
	std::vector<SDL_Rect> spriteClips;

	int clipWidth = spriteTexture.getHeight() / rows;
	int clipHeight = spriteTexture.getWidth() / cols;
	spriteTexture.updateDimensions(clipWidth, clipHeight);

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j <  cols; ++j)
		{
			spriteClips.push_back({ clipWidth * j,
									clipHeight* i,
									clipWidth,
									clipHeight});
		}
	}
	return spriteClips;
}

void close(SDL_Window*& window, SDL_Renderer*& renderer)
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = NULL;
	renderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

