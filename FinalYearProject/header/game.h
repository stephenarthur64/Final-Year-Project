#ifndef GAME_H
#define GAME_H
#include "GameObject.h"
#include "Wall.h"
#include "CollisionManager.h"
#include "Player.h"

enum class GameState {
    TWO_DIMENSION,
    THREE_DIMENSION
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

private:
    Camera3D m_camera;
    Vector3 m_cameraOffset;

    Player m_player;
    Wall m_wall;

    bool m_drawHitboxes;
    GameState m_state = GameState::THREE_DIMENSION;
};

#endif // GAME_H
