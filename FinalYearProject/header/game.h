#ifndef GAME_H
#define GAME_H
#include "GameObject.h"
#include "Wall.h"
#include "CollisionManager.h"

class Game
{
public:
    void init();
    void draw();
    void update();

    void handleInput();
    void collisions();

private:
    Camera3D m_camera;

    GameObject m_player;
    Wall m_wall;

    bool m_drawHitboxes;
};

#endif // GAME_H
