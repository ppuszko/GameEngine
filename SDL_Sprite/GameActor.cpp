#include "GameActor.h"

GameActor::GameActor(std::string name, int maxVel)
{
	this->name = name;
	moveComp.collider.getCollider()->x = 100;
	moveComp.collider.getCollider()->y = 100;
	
}


GameActor::~GameActor()
{
}

void GameActor::move()
{
	moveComp.move();
}

void GameActor::handleEvent(SDL_Event& e)
{
	if (e.type = SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_d:
				moveComp.setVelX(10);
				break;
			case SDLK_a:
				moveComp.setVelX(-10);
				break;
			case SDLK_SPACE:
				if (!moveComp.getIsAirborne())
				{
					moveComp.setIsAirborne(false);
					moveComp.setVelY(10);
				}
		}
		
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_d:
				moveComp.setVelX(-10);
				break;
			case SDLK_a:
				moveComp.setVelX(10);
				break;
		}
	}
}

void GameActor::setCollisionBoxSize(int width, int height)
{
	moveComp.setCollisionBoxSize(width, height);
}
