#include "GameObject.h"

GameObject::GameObject(int maxVel)
{
	MAX_VELOCITY = maxVel;
	posX = 0; 
	posY = 0;
	velX = 0;
	velY = 0;
	
}

GameObject::~GameObject()
{
	sprite.free();
	
}



bool GameObject::initSprite(SDL_Renderer* renderer, std::string path, int cols, int rows)
{
	if (!loadSpriteSheet(this->sprite, renderer, path))
	{
		return false;
	}
	
	else
	{
	sprite.clipSpriteSheet(cols, rows);
	collider.getCollider()->w = sprite.getWidth();
	collider.getCollider()->h = sprite.getHeight();
	/*collisionBox.x -= collisionBox.w / 2;
	collisionBox.y -= collisionBox.h / 2;*/
	return true;
	}
}



//void GameObject::move(SDL_Rect& wall)
//{
//	//vertical movement
//	posX += velX;
//	collisionBox.x = posX;
//
//	//sets velocity to 0 when colliding with object/screen
//	if ((posX < 0) || (posX + collisionBox.w > 576) || checkCollision(collisionBox, wall))
//	{
//		posX -= velX;
//		collisionBox.x = posX;
//	}
//
//	posY += velY;
//	collisionBox.y = posY;
//
//	if ((posY < 0) || (posY + collisionBox.h > 324) || checkCollision(collisionBox, wall))
//	{
//		posY -= velY;
//		collisionBox.y = posY;
//	}
//}

void GameObject::render(int x, int y, SDL_Renderer* renderer, int scale, int& startingFrame)
{
	sprite.renderAnimation(x, y, renderer, sprite.animationClips, startingFrame, scale);
}

//void GameObject::showCollision(SDL_Renderer* renderer)
//{
//	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
//	SDL_RenderDrawRect(renderer, &collisionBox);
//}


//bool checkCollision(SDL_Rect a, SDL_Rect b)
//{	
//	//components of collider's vertexes coordinates
//	int leftA, leftB;
//	int rightA, rightB;
//	int topA, topB;
//	int bottomA, bottomB;
//
//	leftA = a.x;
//	rightA = a.x + a.w;
//	bottomA = a.y + a.h;
//	topA = a.y;
//
//	leftB = b.x;
//	rightB = b.x + b.w;
//	bottomB = b.y + b.h;
//	topB = b.y;
//
//	//this conditions check whether box's axis projections are intersecting. If box's projections are intersecting on both axes, the collision is registered
//
//
//	//since y axis in rendered field is inverted( [0,0] coordinate is in top-left corner), the comparison of Y values has to be inverted too
//	if (bottomA <= topB)
//	{
//		return false;
//	}
//	if (topA >= bottomB)
//	{
//		return false;
//	}
//
//	if (leftA >= rightB)
//	{
//		return false;
//	}
//	if (rightA <= leftB)
//	{
//		return false;
//	}
//
//	return true;
//}
