#include "MoveComponent.h"
//MoveComponent::MoveComponent()
//{
//	posX = 0;
//	posY = 0;
//	velX = 0;
//	velY = 0;
//	isAirborne = true;
//	gravityFactor = 3;
//	airFriction = 0;
//}

MoveComponent::MoveComponent(int positionX, int positionY, int velocityX, int velocityY, int gravityFactor)
{
	posX = positionX;
	posY = positionY;
	velX = velocityX;
	velY = velocityY;
	isAirborne = true;
	this->gravityFactor = gravityFactor;
	airFriction = 0;
}


MoveComponent::~MoveComponent()
{
}

//get a^2 + b^2 part of pythagorean triangle, based on own position and position of currently inspected collider
int MoveComponent::isNearby(Collider& collider)
{
	return (collider.getCollisionBox()->x - posX) * (collider.getCollisionBox()->x - posX) + (collider.getCollisionBox()->y - posY) * (collider.getCollisionBox()->y - posY);
}

//checks for collision with nearby colliders, radius is c^2 part of pythagorean triangle
bool MoveComponent::checkNearbyColliders(Collider& collider, int radius)
{
	for (Collider* obj : Collider::ColliderList)
	{
		if ((obj != &collider) && isNearby(*obj) <= radius*radius)
		{
			if (collider.checkCollision(collider.getCollisionBox(), obj->getCollisionBox()))
			{
				return true;
			}
		}
	}
	return false;
}

void MoveComponent::setIsAirborne(bool value)
{
	isAirborne = value;
}
bool MoveComponent::getIsAirborne()
{
	return isAirborne;
}
void MoveComponent::addVelX(int value)
{
	velX += value;
}
void MoveComponent::addVelY(int value)
{
	velY += value;
}

//updates position based on velocity value, if updating position resulted in collision, reverses position's update
void MoveComponent::move(Collider& collider, const int screenWidth, const int screenHeight, int radius)
{
	posX += velX;
	collider.getCollisionBox()->x = posX;

	if ((posX < 0) || (posX + collider.getWidth() > screenWidth) || checkNearbyColliders(collider, radius))
	{
		posX -= velX;
		collider.getCollisionBox()->x = posX;
	}	
	
	posY += velY;
	collider.getCollisionBox()->y = posY;

	if ((posY < 0) || (posY + collider.getHeight() > screenHeight) || checkNearbyColliders(collider, radius))
	{
		posY -= velY;
		collider.getCollisionBox()->y = posY;
		isAirborne = false;
		velY = 0;
	}
}

void MoveComponent::applyGravity()
{
	velY += gravityFactor;
}


