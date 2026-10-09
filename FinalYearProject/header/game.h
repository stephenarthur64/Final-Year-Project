#ifndef GAME_H
#define GAME_H
#include "GameObject.h"
#include "Wall.h"
#include "CollisionManager.h"
#include "Player.h"
#include "GameState.h"
#include <iostream>

enum Facing {
    NORTH,
    EAST,
    SOUTH,
    WEST,
    END
};

class Game
{
public:
    void init();
    void draw();
    void update();
    void cameraUpdate();

    void handleInput();
    void collisions();
    void swapDimension(GameState t_newState);
    void shiftFacing();

private:
    Camera3D m_camera;
    Vector3 m_cameraOffset;

    Player m_player;
    Wall m_wall;

    bool m_drawHitboxes;
    bool m_selectingDimension = false;
    bool m_canChangeDimension = true;
    GameState m_currentState = GameState::NONE;

    Vector3 m_cameraOffset2D;
    Vector3 m_cameraOffset3D;

    Facing m_facing2D;
    std::string m_compassText;
};

#endif // GAME_H
