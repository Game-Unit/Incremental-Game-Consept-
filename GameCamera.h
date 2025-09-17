#include "raylib.h"
#pragma once

class GameCamera
{
private:
    Camera2D m_camera = { 0 };

    Vector2 m_playerPos = { 0, 300 };

    float m_camSpeed = 5.0f;

    
public:
    GameCamera();
    Camera2D& GetCamera() { return m_camera; }
    void Tick();
};