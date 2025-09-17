#include "raylib.h"
#include "FallingSand.h"

#pragma once

class Building
{
protected:
    Vector2 m_position;
    int m_currentLevel;
    int m_maxLevel;

public:
    Building() = default; 
    Building(Vector2 position); 

    virtual void Upgrade() = 0;
    virtual void Render() = 0;
    virtual void Tick(FallingSand& sandSystem) = 0;
    virtual ~Building() = default;
};