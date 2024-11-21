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

bool MoveComponent::checkNearbyColliders(Collider& collider, int radius)
{
	for (Collider* obj : Collider::ColliderList)
	{
		
		if ((obj != &collider) && isNearby(*obj, radius))
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

int MoveComponent::isNearby(Collider& collider, int radius)
{
	return (collider.getCollisionBox()->x - posX) * (collider.getCollisionBox()->x - posX) + (collider.getCollisionBox()->y - posY) * (collider.getCollisionBox()->y - posY);
}

void MoveComponent::applyGravity()
{
	velY += gravityFactor;
}


