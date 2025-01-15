#include "Collider.h"


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
std::pair<bool, bool> Collider::checkCollisionProjection(SDL_Rect& A, SDL_Rect& B)
{
	std::pair<bool, bool> res({true, false});
	if ( !((A.x + A.w >= B.x) && (A.x <= B.x + B.w)) )
	{
		res.first = false;
		return res;
	}
	if (!((A.y + A.h >= B.y) && (A.y <= B.y + B.h)))
	{
		res.first = false;
		return res;
	}
	if (A.y == B.y + B.h) res.second = true;
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