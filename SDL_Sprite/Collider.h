#pragma once
#include <SDL.h>
#include <vector>
#include <utility>

class Collider
{
public:
	Collider();
	~Collider();
	bool checkCollision(SDL_Rect* A, SDL_Rect* B);
	std::pair<bool, bool> checkCollisionProjection(SDL_Rect& A, SDL_Rect& B);
	void showCollisionBox(SDL_Renderer* renderer);
	void setCollisionBoxSize(int width, int height);
	void drawShape(SDL_Renderer* renderer);
	int getWidth();
	int getHeight();
	int getPosX();
	int getPosY();
	SDL_Rect* getCollisionBox();
	static std::vector<Collider*> ColliderList;
	
protected:
	SDL_Rect collisionBox;
};