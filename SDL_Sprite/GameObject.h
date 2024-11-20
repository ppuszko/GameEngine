#pragma once
#include "Sprite.h"
#include "Collider.h"

class GameObject
{
public:
	GameObject(int maxVel = 10);
	~GameObject();
	int MAX_VELOCITY; 

	bool initSprite(SDL_Renderer* renderer, std::string path, int cols = 1, int rows = 1);
	//handles key presses
	
	//void move(SDL_Rect& wall);
	void render(int x, int y, SDL_Renderer* renderer, int scale, int& startingFrame);


	
protected:
	//coordinates of GameObject
	int posX, posY;
	//velocity of GameObject
	int velX, velY;
	//Collision box
	Sprite sprite;
private:
	Collider collider;
	

};

//bool checkCollision(SDL_Rect a, SDL_Rect b);