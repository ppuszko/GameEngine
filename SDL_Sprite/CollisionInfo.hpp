#pragma once

struct CollisionInfo
{
	bool collisionX;
	bool collisionY;
	bool collidedAbove;

	CollisionInfo(bool x = false, bool y = false, bool a = false)
	{
		collisionX = x;
		collisionY = y;
		collidedAbove = a;
	}
};