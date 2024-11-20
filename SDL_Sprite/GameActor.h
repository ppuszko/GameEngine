#pragma once
#include "MoveComponent.h"
#include "GameObject.h"

class GameActor : public GameObject
{
public:
	GameActor(std::string name, int maxVel);
	~GameActor();
	void move();
	void handleEvent(SDL_Event& e);
	void setCollisionBoxSize(int width, int height);
	MoveComponent moveComp;
protected:
	
	std::string name;
};