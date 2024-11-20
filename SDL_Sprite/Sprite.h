#pragma once
#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

class Sprite
{
public:
	Sprite();
	~Sprite();

	void free();
	bool loadFromFile(std::string path, SDL_Renderer* renderer);
	void clipSpriteSheet(int cols, int rows);
	void render(int x, int y, SDL_Renderer* renderer,  SDL_Rect* clip = NULL, int scale = 1, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void renderAnimation(int x, int y, SDL_Renderer* renderer, std::vector<SDL_Rect>& clip, int& startingFrame, int scale = 1, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	

	int getWidth() const;
	int getHeight() const;
	std::vector<SDL_Rect> getAnimationClips() const;
	void updateDimensions(int width, int height);

	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void setBlendMode(SDL_BlendMode blending);
	void setAlpha(Uint8 alpha);
	std::vector<SDL_Rect> animationClips;
private:
	SDL_Texture* sTexture;
	
	int sWidth;
	int sHeight;

};

bool init(SDL_Window*& window, SDL_Renderer*& renderer, int width, int height);
bool loadSpriteSheet(Sprite& spriteTexture, SDL_Renderer* renderer, std::string path);
std::vector<SDL_Rect> clipSpriteSheet(Sprite& spriteTexture, int cols, int rows);
void close(SDL_Window*& window, SDL_Renderer*& renderer);
