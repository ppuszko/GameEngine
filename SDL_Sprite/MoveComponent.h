#pragma once
#include <SDL.h>
#include "Collider.h"

class MoveComponent
{
public:
	/*MoveComponent();*/
	MoveComponent(int positionX = 0, int positionY = 0, int velocityX = 0, int velocityY = 0, int gravityFactor = 1);
	~MoveComponent();

	bool checkNearbyColliders(Collider& collider, int radius);
	void setIsAirborne(bool value);
	bool getIsAirborne();
	void addVelX(int value);
	void addVelY(int value);
	void move(Collider& collider, const int screenWidth, const int screenHeight, int radius=100);
	int isNearby(Collider& collider, int radius);
	void applyGravity();


private:
	int posX, posY;
	int velX, velY;
	bool isAirborne;
	int airFriction;
	int gravityFactor;
	
};