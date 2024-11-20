#pragma once
#include <SDL.h>
#include <vector>

class Collider
{
public:
	Collider();
	~Collider();
	bool checkCollision(SDL_Rect* A, SDL_Rect* B);
	void showCollisionBox(SDL_Renderer* renderer);
	void setCollisionBoxSize(int width, int height);
	int getWidth();
	int getHeight();
	int getPosX();
	int getPosY();
	SDL_Rect* getCollider();
	static std::vector<Collider*> ColliderList;
	
private:
	
	SDL_Rect collisionBox;
};