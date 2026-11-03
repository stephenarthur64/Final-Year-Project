#pragma once
#include "Wall.h"
#include <raylib.h>
#include <raymath.h>

class MovingWall :
    public Wall
{
public:
    MovingWall(Vector3 t_pos, float t_l, float t_w, float t_h, Vector3 t_upLimit, Vector3 t_lowLimit);
    virtual void update() override;

private:
    Vector3* m_target;
    Vector3 m_direction;
    Vector3 m_upperLimit;
    Vector3 m_lowerLimit;
};

