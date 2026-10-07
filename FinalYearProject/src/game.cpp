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

}

void Game::update()
{
    UpdateCamera(&m_camera, CAMERA_CUSTOM);

    handleInput();
    collisions();

    m_player.move();
}

void Game::handleInput()
{
    Vector3 force = { 0.0f, 0.0f, 0.0f };

    if (IsKeyDown(KEY_W))
    {
        force.x = -1.0f;
    }
    if (IsKeyDown(KEY_A))
    {
        force.z = 1.0f;
    }
    if (IsKeyDown(KEY_S))
    {
        force.x = 1.0f;
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

    m_player.applyForce(force);
}

void Game::collisions()
{
    if (CheckCollisionBoxes(m_player.getNextHitbox(1,1,1), m_wall.getHitbox()))
    {
        CollisionManager::BoxCollisions(m_player, m_wall);
    }
}
