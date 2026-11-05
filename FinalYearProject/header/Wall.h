#pragma once
#include "GameObject.h"
#include <iostream>

class Wall :
    public GameObject
{
public:
    Wall(Vector3 t_pos, float t_l, float t_w, float t_h);
    Wall(Vector3 t_pos, float t_l, float t_w, float t_h, Color t_c);
    ~Wall();
    virtual void update() override;
    BoundingBox getLowHitbox();
};

