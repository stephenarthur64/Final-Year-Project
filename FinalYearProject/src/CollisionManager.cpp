#include "CollisionManager.h"

void CollisionManager::BoxCollisions(GameObject& t_go1, GameObject& t_go2)
{
	// Collision on x axis
	if (CheckCollisionBoxes(t_go1.getNextHitbox(1, 0, 0), t_go2.getHitbox()))
	{
		t_go1.stopVelocity(0, 1, 1); // Stop x velocity
	}

	// Collision on y axis
	if (CheckCollisionBoxes(t_go1.getNextHitbox(0, 1, 0), t_go2.getHitbox()))
	{
		t_go1.stopVelocity(1, 0, 1); // Stop y velocity
	}

	// Collision on z axis
	if (CheckCollisionBoxes(t_go1.getNextHitbox(0, 0, 1), t_go2.getHitbox()))
	{
		t_go1.stopVelocity(1, 1, 0); // Stop z velocity
	}
}
