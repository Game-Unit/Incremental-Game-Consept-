#include "raylib.h"
#pragma once

class GameSetting
{
private:
    // Private constructor so no one can create objects outside
    GameSetting() 
    {

    }

    // Prevent copying
    GameSetting(const GameSetting&) = delete;
    GameSetting& operator=(const GameSetting&) = delete;

    const int baseWidth = 320;
    const int baseHeight = 180;

    float m_scaleX = 1.0;
    float m_scaleY = 1.0;

    float m_gameScale = 1.0f;

public:
    // Static method to access the instance
    static GameSetting& Instance()
    {
        static GameSetting instance; // Created once, reused after
        return instance;
    }

    float GetGameScale() { return m_gameScale; }
    void ChangeGameScale();
};