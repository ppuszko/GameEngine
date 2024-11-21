#include "GameActor.h"

GameActor::GameActor(int maxVel, int x, int y, int collWidth, int collHeight, int gravityFactor)
{

	
	moveComp = MoveComponent(x, y, 0, 0, gravityFactor);
	collider.getCollisionBox()->x = x;
	collider.getCollisionBox()->y = y;
	collider.getCollisionBox()->w = collWidth;
	collider.getCollisionBox()->h = collHeight;
}


GameActor::~GameActor()
{
}

void GameActor::move(int screenWidth, int screenHeight, int radius)
{
	moveComp.move(this->collider, screenWidth, screenHeight, radius);
	
}

//temporary key assignments to check if this code works 
void GameActor::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_d:
				moveComp.addVelX(10);
				break;
			case SDLK_a:
				moveComp.addVelX(-10);
				break;
			case SDLK_SPACE:
				if (moveComp.getIsAirborne() == false)
				{
					moveComp.addVelY(-25);
					moveComp.setIsAirborne(true);
				}
		}
		
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_d:
				moveComp.addVelX(-10);
				break;
			case SDLK_a:
				moveComp.addVelX(10);
				break;
		}
	}
}


void GameActor::applyGravity()
{
	moveComp.applyGravity();
}


