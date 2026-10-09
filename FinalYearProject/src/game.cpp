#include "raylib.h"
#include "stdio.h"
#include "../header/game.h"

void Game::init()
{
    m_camera.position = { 10.0f, 10.0f, 10.0f };
    m_camera.target = { 0.0f, 0.0f, 0.0f };     
    m_camera.up = { 0.0f, 1.0f, 0.0f };    
    m_camera.fovy = 45.0f;                                
    m_camera.projection = CAMERA_PERSPECTIVE;

    m_drawHitboxes = false;

    m_player.setHitbox();
    m_wall.setHitbox();

    swapDimension(GameState::THREE_DIMENSION);
}

void Game::draw()
{
    DrawFPS(0, 0);

    BeginMode3D(m_camera);

    DrawCube({0.0f, 0.0f, 0.0f}, 20.0f, 2.0f, 20.0f, GRAY);
    DrawCubeWires({0.0f, 0.0f, 0.0f}, 20.0f, 2.0f, 20.0f, BLACK);

    m_player.draw();
    m_wall.draw();

    DrawGrid(10, 1.0f);

    EndMode3D();

    if (m_selectingDimension)
    {
        DrawRectangleLinesEx({ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() }, 10.0f, BLUE);
    }
}

void Game::update()
{
    UpdateCamera(&m_camera, CAMERA_CUSTOM);

    handleInput();
    collisions();

    if (!m_selectingDimension)
    {
        m_player.move();
    }
    cameraUpdate();
}

void Game::cameraUpdate()
{
    m_camera.position = m_player.getPosition();
    m_camera.position += m_cameraOffset;
    m_camera.target = m_player.getPosition();
}

void Game::handleInput()
{
    Vector3 force = { 0.0f, 0.0f, 0.0f };

    if (!m_selectingDimension)
    {
        if (m_currentState == GameState::THREE_DIMENSION)
        {
            if (IsKeyDown(KEY_W))
            {
                force.x = -1.0f;
            }
            if (IsKeyDown(KEY_S))
            {
                force.x = 1.0f;
            }
        }
        if (IsKeyDown(KEY_A))
        {
            force.z = 1.0f;
        }
        if (IsKeyDown(KEY_D))
        {
            force.z = -1.0f;
        }
        if (IsKeyReleased(KEY_F1))
        {
            m_player.toggleHitbox();
            m_wall.toggleHitbox();
        }
    }

    if (IsKeyReleased(KEY_G))
    {
        m_selectingDimension = !m_selectingDimension;
    }

    if (IsKeyReleased(KEY_TWO) && m_selectingDimension)
    {
        swapDimension(GameState::TWO_DIMENSION);
    }
    if (IsKeyReleased(KEY_THREE) && m_selectingDimension)
    {
        swapDimension(GameState::THREE_DIMENSION);
    }

    m_player.applyForce(force);
}

void Game::collisions()
{
    if (CheckCollisionBoxes(m_player.getNextHitbox(1, 1, 1), m_wall.getHitbox()))
    {
        //CollisionManager::BoxCollisions(m_player, m_wall);

        Ray ray = { 0 };
        ray.position = m_player.getPosition();
        ray.direction = m_player.getDirection();
        RayCollision collision = { 0 };
        collision.distance = 10.0f;
        collision.hit = false;

        collision = GetRayCollisionBox(ray, m_wall.getHitbox());

        if (collision.hit)
        {
            m_player.repulsiveForce(collision);
        }
    }
}

void Game::swapDimension(GameState t_newState)
{
    if (m_currentState != t_newState)
    {
        m_currentState = t_newState;

        if (m_currentState == GameState::TWO_DIMENSION)
        {
            m_camera.projection = CAMERA_ORTHOGRAPHIC;
            m_cameraOffset = { 10.0f, 0.0f, 0.0f };
        }
        else if (m_currentState == GameState::THREE_DIMENSION)
        {
            m_camera.projection = CAMERA_PERSPECTIVE;
            m_cameraOffset = { 10.0f, 3.0f, 0.0f };
        }

        m_player.swapDimension(m_currentState);
        m_wall.swapDimension(m_currentState);
    }
}
