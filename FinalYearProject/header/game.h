#ifndef GAME_H
#define GAME_H
#include "GameObject.h"
#include "Wall.h"
#include "MovingWall.h"
#include "Player.h"
#include "GameState.h"
#include <iostream>
#include <vector>

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
    void resetCollisionRay();
    void collisions();
    void swapDimension(GameState t_newState);
    void shiftFacing();

private:
    Camera3D m_camera;
    Camera3D m_camera2D;
    Camera3D* m_currentCamera;
    Vector3 m_cameraOffset;

    Player m_player;
    std::vector<std::shared_ptr<Wall>> m_walls;

    bool m_drawHitboxes;
    bool m_selectingDimension = false;
    bool m_canChangeDimension = true;
    GameState m_currentState = GameState::NONE;

    Vector3 m_cameraOffset2D;
    Vector3 m_cameraOffset3D;

    Facing m_facing2D;
    std::string m_compassText;

    static const int DIRECTION_RAY_AMOUNT = 5;
    Vector3 m_collisionRayDirections[DIRECTION_RAY_AMOUNT] = { {1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, -1.0f, 0.0f} };
    Ray m_collideRay = { 0 };
    RayCollision m_collideResult = { 0 };

    Vector3 m_cameraForward;
    Vector3 m_cameraRight;
    Vector3 m_cameraTarget = { 0.0f, 0.0f, 0.0f };

    Vector3 m_currentActiveAxis = { 1.0f, 1.0f, 1.0f };
};

#endif // GAME_H