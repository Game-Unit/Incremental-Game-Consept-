#include "raylib.h"
#include "GameSetting.h"

#include <random>

#pragma once

#define SCALE GameSetting::Instance().GetGameScale()

struct Cell
{
    int x, y;
    int value = 0;
};

enum DrawType
{
    sand,
    hardObject,
    erase
};

class FallingSand
{
private:
    int m_positionX;
    int m_positionY;

    int m_width;
    int m_height;

    float m_accumulator = 0.0f;
    const float m_fixedTimeStep = 1.0f / 160.0f;

    const int m_gridSize = 1;
    int m_columns;
    int m_rows;
    std::vector<std::vector<Cell>> m_grid;

    std::random_device m_rd;
    std::mt19937 m_rng;

    std::vector<int> m_columnOrder;

public:
    FallingSand(int posX, int PosY, int width, int height);

    void Update();

    void SetCell(int posX, int PosY, int value = 1);

    int GetValueFromWroldPos(int worldX, int worldY);
    Vector2 GetCellPosFromWorld(int worldX, int worldY);

    int GetPosX() const { return m_positionX; }
    int GetPosY() const { return m_positionY; }
    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }
};