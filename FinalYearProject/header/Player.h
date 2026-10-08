#pragma once
#include "../header/GameObject.h"
class Player :
    public GameObject
{
public:
    Player() {}
    void repulsiveForce(RayCollision t_rc);
};

