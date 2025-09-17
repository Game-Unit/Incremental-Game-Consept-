#include "GameCamera.h"

GameCamera::GameCamera()
{
    m_camera.target = (Vector2){ 0, 0 };                 // The point the camera looks at in the world
    m_camera.offset = (Vector2){ (float)(GetScreenWidth()/2), (float)(GetScreenHeight()/2) }; // Position of target on screen
    m_camera.rotation = 0.0f;
    m_camera.zoom = 1.0f;  
}

void GameCamera::Tick()
{
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) m_playerPos.x += m_camSpeed;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))  m_playerPos.x -= m_camSpeed;

    m_camera.target = m_playerPos;
}