#include "raylib.h"
#include "Animation.h"
#include "FallingSand.h"

#include <vector>
#include <iostream>

#pragma once

class Worker
{
private:
    float m_speed;
    Vector2 m_position;

    std::vector<Vector2> m_positionsToGo;

    Animation m_anim;
    Texture2D m_texture;

    int m_maxSandHold = 5;
    int m_currentSandHold = 0;

    bool m_forward = true;
    int m_currentIndex = 0;

public:
    Worker(Vector2 startPos, std::vector<Vector2> positionsToGo);
    ~Worker();

    void Update(FallingSand& fallingSand);
    void Render(FallingSand& fallingSand);
};