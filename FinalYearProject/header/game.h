#ifndef GAME_H
#define GAME_H
#include "GameObject.h"
#include "Wall.h"
#include "CollisionManager.h"
#include "Player.h"
#include "GameState.h"

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

private:
    Camera3D m_camera;
    Vector3 m_cameraOffset;

    Player m_player;
    Wall m_wall;

    bool m_drawHitboxes;
    bool m_selectingDimension = false;
    GameState m_currentState = GameState::NONE;
};

#endif // GAME_H
