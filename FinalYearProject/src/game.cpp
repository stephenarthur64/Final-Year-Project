#include "raylib.h"
#include "stdio.h"
#include "../header/game.h"

void Game::init()
{
    DisableCursor();

    m_cameraOffset2D = { 10.0f, 0.0f, 0.0f };
    m_cameraOffset3D = { 10.0f, 3.0f, 0.0f };

    m_camera.position = { 10.0f, 10.0f, 10.0f };
    m_camera.position += m_cameraOffset3D;
    m_camera.target = { 0.0f, 0.0f, 0.0f };     
    m_camera.up = { 0.0f, 1.0f, 0.0f };    
    m_camera.fovy = 45.0f;                                
    m_camera.projection = CAMERA_PERSPECTIVE;

    m_camera2D.position = { 10.0f, 0.0f, 0.0f };
    m_camera2D.position += m_cameraOffset2D;
    m_camera2D.target = { 0.0f, 0.0f, 0.0f };     
    m_camera2D.up = { 0.0f, 1.0f, 0.0f };    
    m_camera2D.fovy = 45.0f;                                
    m_camera2D.projection = CAMERA_ORTHOGRAPHIC;

    m_currentCamera = &m_camera;

    m_drawHitboxes = false;

    m_player.setHitbox();
    m_wall.setHitbox();

    m_facing2D = Facing::NORTH;

    swapDimension(GameState::THREE_DIMENSION);
}

void Game::draw()
{
    DrawFPS(0, 0);

    BeginMode3D(*m_currentCamera);

    DrawCube({ 0.0f, 0.0f, 0.0f }, 20.0f, 2.0f, 20.0f, GRAY);
    DrawCubeWires({ 0.0f, 0.0f, 0.0f }, 20.0f, 2.0f, 20.0f, BLACK);

    m_player.draw();
    m_wall.draw();

    DrawGrid(10, 1.0f);

    EndMode3D();

    if (m_selectingDimension)
    {
        if (m_canChangeDimension)
        {
            DrawRectangleLinesEx({ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() }, 10.0f, BLUE);
        }
        else
        {
            DrawRectangleLinesEx({ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() }, 10.0f, RED);
        }

        DrawText(m_compassText.c_str(), 20, 20, 30, BLACK);
    }
}

void Game::update()
{
    UpdateCameraPro(m_currentCamera, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 0.0f);

    handleInput();

    if (!m_selectingDimension)
    {
        m_player.move();
    }
    collisions();
    cameraUpdate();
}

void Game::cameraUpdate()
{
    if (m_currentState == GameState::THREE_DIMENSION)
    {
        Vector2 change = Vector2Normalize(GetMouseDelta());
        change *= 4.0f;

        Matrix m1, m2;
        m1 = GetCameraMatrix(m_camera);
        m2 = GetCameraMatrix(m_camera);
        m1 = MatrixRotateX(-change.y * DEG2RAD);
        m2 = MatrixRotateY(-change.x * DEG2RAD);
        
        Quaternion q1 = QuaternionFromMatrix(m1);
        Quaternion q2 = QuaternionFromMatrix(m2);

        m_camera.position.y = Vector3RotateByQuaternion(m_camera.position, q1).y;
        m_camera.position.y = Clamp(m_camera.position.y, -10.0f, 10.0f);
        m_camera.position.x = Vector3RotateByQuaternion(m_camera.position, q1).x;
        m_camera.position.y = Clamp(m_camera.position.y, -10.0f, 10.0f);
        m_camera.position = Vector3RotateByQuaternion(m_camera.position, q2);
    }

    m_cameraForward = m_currentCamera->position - m_camera.target;
    m_cameraForward = Vector3Normalize(m_cameraForward);
    m_cameraRight = Vector3RotateByAxisAngle(m_cameraForward, {0.0f, 1.0f, 0.0f}, 90 * DEG2RAD);
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
                force -= m_cameraForward;
            }
            if (IsKeyDown(KEY_S))
            {
                force += m_cameraForward;
            }
        }
        if (IsKeyDown(KEY_A))
        {
            force -= m_cameraRight;
        }
        if (IsKeyDown(KEY_D))
        {
            force += m_cameraRight;
        }
        force.y = 0.0f;
        if (IsKeyReleased(KEY_F1))
        {
            m_player.toggleHitbox();
            m_wall.toggleHitbox();
        }
    }

    if (IsKeyReleased(KEY_G))
    {
        collisions();
        if (m_canChangeDimension)
        {
            m_selectingDimension = !m_selectingDimension;
        }
    }

    if (m_selectingDimension)
    {
        if (IsKeyReleased(KEY_Q))
        {
            m_facing2D = (Facing)(m_facing2D - 1);
            if (m_facing2D < 0)
            {
                m_facing2D = Facing::WEST;
            }
            shiftFacing();
        }
        if (IsKeyReleased(KEY_E))
        {
            m_facing2D = (Facing)(m_facing2D + 1);
            if (m_facing2D >= Facing::END)
            {
                m_facing2D = Facing::NORTH;
            }
            shiftFacing();
        }
    }

    if (IsKeyReleased(KEY_TWO) && m_selectingDimension)
    {
        swapDimension(GameState::TWO_DIMENSION);
    }
    if (IsKeyReleased(KEY_THREE) && m_selectingDimension)
    {
        swapDimension(GameState::THREE_DIMENSION);
    }

    if (m_currentState == GameState::TWO_DIMENSION)
    {
        force.x = 0.0f;
    }
    m_player.applyForce(force);
}

void Game::resetCollisionRay()
{
    m_collideRay = { 0 };
    m_collideResult = { 0 };
    m_collideRay.position = m_player.getPosition();
    m_collideResult.distance = 10.0f;
    m_collideResult.hit = false;
}

void Game::collisions()
{
    if (CheckCollisionBoxes(m_player.getNextHitbox(), m_wall.getHitbox()))
    {
        if (m_selectingDimension)
        {
            m_canChangeDimension = false;
            return;
        }
        else
        {
            resetCollisionRay();

            for (int i = 0; i < 4; i++)
            {
                m_collideRay.direction = m_collisionRayDirections[i];
                m_collideResult = GetRayCollisionBox(m_collideRay, m_wall.getHitbox());

                if (m_collideResult.hit)
                {
                    m_player.repulsiveForce(m_collideResult);
                }
            }
        }
    }

    if (m_selectingDimension)
    {
        m_canChangeDimension = true;
    }
}

void Game::swapDimension(GameState t_newState)
{
    if (m_currentState != t_newState)
    {
        m_currentState = t_newState;

        if (m_currentState == GameState::TWO_DIMENSION)
        {
            m_currentCamera = &m_camera2D;
            m_cameraOffset = m_cameraOffset2D;
            shiftFacing();
        }
        else if (m_currentState == GameState::THREE_DIMENSION)
        {
            m_currentCamera = &m_camera;
            m_cameraOffset = m_cameraOffset3D;
        }

        m_player.swapDimension(m_currentState);
        m_wall.swapDimension(m_currentState);
    }
}

void Game::shiftFacing()
{
    switch (m_facing2D)
    {
    case NORTH:
        m_camera2D.position = { 10.0f, 0.0f, 0.0f };
        m_compassText = "North";
        break;
    case SOUTH:
        m_camera2D.position = { -10.0f, 0.0f, 0.0f };
        m_compassText = "South";
        break;
    case EAST:
        m_camera2D.position = { 0.0f, 0.0f, 10.0f };
        m_compassText = "East";
        break;
    case WEST:
        m_camera2D.position = { 0.0f, 0.0f, -10.0f };
        m_compassText = "West";
        break;
    default:
        break;
    }
}
