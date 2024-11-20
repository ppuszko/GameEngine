#include "MoveComponent.h"

MoveComponent::MoveComponent(int positionX, int positionY, int velocityX, int velocityY, int gravityFactor)
{
	posX = positionX;
	posY = positionY;
	velX = velocityX;
	velY = velocityY;
	isAirborne = true;
	gravityFactor = gravityFactor;
	airFriction = 0;
}

MoveComponent::~MoveComponent()
{
}

bool MoveComponent::checkNearbyColliders(int velocityX, int velocityY)
{
	for (Collider* obj : Collider::ColliderList)
	{
		int distX = abs(collider.getPosX() - obj->getPosX());
		int distY = abs(collider.getPosY() - obj->getPosY());
		if ((obj != &this->collider) || (distX < velX * 10) || (distY < velY * 10))
		{
			if (collider.checkCollision(collider.getCollider(), obj->getCollider()))
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

void MoveComponent::setVelX(int value)
{
	velX += value;
}

void MoveComponent::setVelY(int value)
{
	velY -= value;
}

void MoveComponent::move()
{
	posX += velX;
	collider.getCollider()->x = posX;

	if ((posX < 0) || (posX + collider.getWidth() > 576) || checkNearbyColliders())
	{
		posX -= velX;
		collider.getCollider()->x = posX;
	}

	velY != 0 ? velY += gravityFactor : velY = 0;
	posY += velY;
	collider.getCollider()->y = posY;

	if ((posY < 0) || (posY + collider.getHeight() > 324) || (checkNearbyColliders()))
	{
		velY = 0;
		collider.getCollider()->y = posY + 1;
		isAirborne = false;
		
	}
	else
	{
		isAirborne = true;
		velY += 10;
	}

	
}

void MoveComponent::setCollisionBoxSize(int width, int height)
{
	collider.setCollisionBoxSize(width, height);
}
