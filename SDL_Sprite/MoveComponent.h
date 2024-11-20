#pragma once
#include <SDL.h>
#include "Collider.h"

class MoveComponent
{
public:
	MoveComponent(int positionX = 0, int positionY = 0, int velocityX = 10, int velocityY = 10, int gravityFactor = 3);
	~MoveComponent();

	bool checkNearbyColliders(int velocityX = 10, int veocitylY = 10);
	void setIsAirborne(bool value);
	bool getIsAirborne();
	void setVelX(int value);
	void setVelY(int value);
	void move();
	void setCollisionBoxSize(int width, int height);
	Collider collider;
private:
	int posX, posY;
	int velX, velY;
	bool isAirborne;
	int airFriction;
	int gravityFactor;
	
};