#include "GameActor.h"

GameActor::GameActor(int maxVel, int x, int y, int collWidth, int collHeight, int gravityFactor)
{

	maxVelocity = maxVel;
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
	moveComp.move(this->collider, screenWidth, screenHeight, dt, radius);
	
}

//temporary key assignments to check if this code works 
void GameActor::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		dt.initLastTime();
		switch (e.key.keysym.sym)
		{
			case SDLK_d:
				moveComp.addVelX(maxVelocity);
				break;
			case SDLK_a:
				moveComp.addVelX(-maxVelocity);
				break;
			case SDLK_SPACE:
				if (moveComp.getIsAirborne() == false)
				{
					moveComp.addVelY(-450);
					moveComp.setIsAirborne(true);
				}
		}
		
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{       
		dt.initLastTime();
		switch (e.key.keysym.sym)
		{
			case SDLK_d:
				moveComp.addVelX(-maxVelocity);
				break;
			case SDLK_a:
				moveComp.addVelX(maxVelocity);
				break;
		}
	}
}


void GameActor::applyGravity()
{
	moveComp.applyGravity(dt);
}


