#include "Collider.h"
#include <iostream>

Collider::Collider()
{
	collisionBox = { 0,0,0,0 };
	ColliderList.push_back(this);
}

Collider::~Collider()
{
	ColliderList.erase(std::remove(ColliderList.begin(), ColliderList.end(), this), ColliderList.end());
}

bool Collider::checkCollision(SDL_Rect* A, SDL_Rect* B)
{
	return SDL_HasIntersection(A, B);
}

// first parameter tells if there was a collision at all, second parameter tells if object should continue falling after colliding.
CollisionInfo Collider::checkCollisionProjection(SDL_Rect& A, SDL_Rect& B)
{
	CollisionInfo res;
	if ( !((A.x + A.w >= B.x) && (A.x <= B.x + B.w)) )
	{
		return res;
	}
	if (!((A.y + A.h >= B.y) && (A.y <= B.y + B.h)))
	{
		return res;
	}
	
	if (abs(A.x + A.w - B.x) <= marginDifference || abs(A.x - B.x - B.  w) <= marginDifference) res.collisionX = true;
	
	if (abs(A.y - B.y - B.h) <= marginDifference)
	{
		res.collisionY = true;
		res.collidedAbove = true;
	}
	else if (abs(A.y + A.h - B.y) <= marginDifference)
	{
		res.collisionY = true;
		res.collidedAbove = false;
	}
	std::cout << "X: " << res.collisionX << " Y: " << res.collisionY << " airborne: " << res.collidedAbove << std::endl;

	return res;
}


void Collider::showCollisionBox(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &collisionBox);
}

void Collider::drawShape(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &collisionBox);
}

void Collider::setCollisionBoxSize(int width, int height)
{
	collisionBox.w = width;
	collisionBox.h = height;
}

int Collider::getWidth()
{
	return collisionBox.w;
}
int Collider::getHeight()
{
	return collisionBox.h;
}
int Collider::getPosX()
{
	return collisionBox.x;
}
int Collider::getPosY()
{
	return collisionBox.y;
}

SDL_Rect* Collider::getCollisionBox()
{
	return &collisionBox;
}
//static list of every instantiaded collider, used to check for collision in MoveComp
std::vector<Collider*> Collider::ColliderList;