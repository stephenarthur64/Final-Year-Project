#pragma once
#include "GameObject.h"
class Wall :
    public GameObject
{
public:
    Wall(Vector3 t_pos, float t_l, float t_w, float t_h);
};

