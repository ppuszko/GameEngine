#pragma once
#include "Sprite.h"
#include "Collider.h"

class GameObject
{
public:
	GameObject(int x=0, int y=0, int w = 0, int h = 0);
	~GameObject();
	

	bool initSprite(SDL_Renderer* renderer, std::string path, int cols = 1, int rows = 1);
	void render(SDL_Renderer* renderer, int scale = 1);
	void renderAnimation(SDL_Renderer* renderer, int& startingFrame, int scale = 1);
	void setCollisionBoxSize(int width, int height);
	void showCollisionBox(SDL_Renderer* renderer);

	
protected:	
	//Collision box
	Sprite sprite;
	Collider collider;
	

};

