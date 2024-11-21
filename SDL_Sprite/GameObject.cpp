#include "GameObject.h"

GameObject::GameObject(int x, int y, int w, int h)
{
	
	collider.getCollisionBox()->x = x;
	collider.getCollisionBox()->y = y;
	collider.getCollisionBox()->w = w;
	collider.getCollisionBox()->h = h;
	
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
		if (cols > 1 || rows > 1)
		{
			sprite.clipSpriteSheet(cols, rows);
		}
		collider.getCollisionBox()->w = sprite.getWidth();
		collider.getCollisionBox()->h = sprite.getHeight();
		
	/*collisionBox.x -= collisionBox.w / 2;
	collisionBox.y -= collisionBox.h / 2;*/
	return true;
	}
}

void GameObject::render(SDL_Renderer* renderer, int scale)
{
	int x{ collider.getCollisionBox()->x };
	int y{ collider.getCollisionBox()->y };
	sprite.render(x, y, renderer);
}

void GameObject::renderAnimation(SDL_Renderer* renderer, int& startingFrame, int scale)
{
	int x{ collider.getCollisionBox()->x };
	int y{ collider.getCollisionBox()->y };
	sprite.renderAnimation(x, y, renderer, sprite.animationClips, startingFrame, scale);
	collider.getCollisionBox()->x = x;
	collider.getCollisionBox()->y = y;
}

void GameObject::setCollisionBoxSize(int width, int height)
{
	collider.getCollisionBox()->w = width;
	collider.getCollisionBox()->h = height;
}

void GameObject::showCollisionBox(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(renderer, collider.getCollisionBox());
}


