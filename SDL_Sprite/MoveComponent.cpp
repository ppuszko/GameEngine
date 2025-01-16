#include "MoveComponent.h"
#include <iostream>
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

//checks for collision with nearby colliders, radius is c part of pythagorean triangle
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

CollisionInfo MoveComponent::checkNearbyCollidersProjection(Collider& collider, int radius)
{
	auto c = collider.getCollisionBox();
	std::cout << "actor  x: " << c->x << " w: " << c->w << " y: " << c->y << " h: " << c->h << std::endl;
	for (Collider* obj : Collider::ColliderList)
	{
		if ((obj != &collider) /* && isNearby(*obj) <= radius * radius*/)
		{
			c = obj->getCollisionBox();
			std::cout << "x: " << c->x << " w: " << c->w << " y: " << c->y << " h: " << c->h << std::endl;
			return collider.checkCollisionProjection(*collider.getCollisionBox(), *obj->getCollisionBox());
		}
	}
	return new CollisionInfo;
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
void MoveComponent::move(Collider& collider, const int screenWidth, const int screenHeight, DeltaTime& dt, int radius)
{
	

	float delta = dt.getDeltaTime();
	float targetX = posX + velX * delta;
	collider.getCollisionBox()->x = targetX;

	auto collisionResult = checkNearbyCollidersProjection(collider, radius);
	
	if ((targetX < 0) || (targetX + collider.getWidth() > screenWidth) || collisionResult.collisionX)
	{
		std::cout << "Collision in X detected!" << std::endl;
		targetX = posX;
	}	
	posX = targetX;
	collider.getCollisionBox()->x = posX;

	//delta = dt.getDeltaTime();
	float targetY = posY + velY * delta;

	collider.getCollisionBox()->y = targetY;
	collisionResult = checkNearbyCollidersProjection(collider, radius);

	if ((targetY < 0) || (targetY + collider.getHeight() > screenHeight) || collisionResult.collisionY)
	{	
		std::cout << "collision in Y detected, airborne =  "<< isAirborne << std::endl;
		targetY = posY;
		isAirborne = collisionResult.collidedAbove;
		velY = 0;
	}

	
	posY = targetY;
	collider.getCollisionBox()->y = posY;
	
}

void MoveComponent::applyGravity(DeltaTime &dt)
{
	velY += gravityFactor;
}


