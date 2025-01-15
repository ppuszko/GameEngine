#pragma once
#include "MoveComponent.h"
#include "GameObject.h"

class GameActor : public GameObject
{
public:
	GameActor(int maxVel, int x, int y, int collWidth = 0, int collHeight = 0, int gravityFactor = 15);
	~GameActor();
	void move(int screenWidth, int screenHeight, int radius = 100);
	void handleEvent(SDL_Event& e);
	void applyGravity();
	
protected:
	MoveComponent moveComp;
	int maxVelocity;
	DeltaTime dt;

};