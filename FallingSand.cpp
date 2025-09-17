#include "FallingSand.h"

#include <vector>
#include <numeric>
#include <algorithm>

#define SCALE GameSetting::Instance().GetGameScale()

FallingSand::FallingSand(int posX, int PosY, int width, int height)
    : m_positionX(posX), m_positionY(PosY), m_width(width), m_height(height), m_rng(m_rd())
{
    m_columns = m_width / m_gridSize;
    m_rows = m_height / m_gridSize;

    // Resize grid
    m_grid.resize(m_columns, std::vector<Cell>(m_rows));

    // Fill grid with positions
    for (int x = 0; x < m_columns; x++)
    {
        for (int y = 0; y < m_rows; y++)
        {
            m_grid[x][y] = {x, y, 0};
        }
    }

    // Build column order
    m_columnOrder.resize(m_columns);
    std::iota(m_columnOrder.begin(), m_columnOrder.end(), 0);
}

void FallingSand::Update()
{
    m_accumulator += GetFrameTime();
    while (m_accumulator >= m_fixedTimeStep)
    {
        std::shuffle(m_columnOrder.begin(), m_columnOrder.end(), m_rng);
        bool updated[m_columns][m_rows]{false};
        for (int xi = 0; xi < m_columns; xi++)
        {
            int x = m_columnOrder[xi];
            for (int y = m_rows - 1; y >= 0; --y)
            {
                if (m_grid[x][y].value == 1 && !updated[x][y])
                {
                    int newX = x;
                    int newY = y;

                    // Try to move down
                    if (y + 1 < m_rows && m_grid[x][y + 1].value == 0)
                    {
                        newY = y + 1;
                    }
                    else if (y + 1 < m_rows && m_grid[x][y + 1].value != 0 && !updated[x][y + 1])
                    {
                        // Optionally slide left/right

                        // printf(TextFormat("%i", StillFalling(x, y)));
                        bool canLeft = (x - 1 >= 0) && (m_grid[x - 1][y + 1].value == 0) && (m_grid[x - 1][y].value != 2);
                        bool canRight = (x + 1 < m_columns) && (m_grid[x + 1][y + 1].value == 0) && (m_grid[x + 1][y].value != 2);

                        if (canLeft || canRight)
                        {
                            int side = 0;
                            if (canLeft && canRight)
                                side = (rand() % 2) ? -1 : 1;
                            else
                                side = canLeft ? -1 : 1;

                            newX = x + side;
                            newY = y + 1;
                        }
                    }

                    if (newX != x || newY != y)
                    {
                        m_grid[x][y].value = 0;
                        m_grid[newX][newY].value = 1;
                        updated[x][y] = true;
                        updated[newX][newY] = true;
                    }
                }
            }
        }
        m_accumulator -= m_fixedTimeStep;
    }

    for (int x = 0; x < m_columns; x++)
    {
        for (int y = 0; y < m_rows; y++)
        {
            m_grid[x][y].x = x * m_gridSize;
            m_grid[x][y].y = y * m_gridSize;

            //DrawRectangleLines((m_grid[x][y].x + m_positionX) * SCALE, (m_grid[x][y].y + m_positionY) * SCALE, m_gridSize * SCALE, m_gridSize * SCALE, GRAY);

            if (m_grid[x][y].value == 1)
                DrawRectangle((m_grid[x][y].x + m_positionX) * SCALE, (m_grid[x][y].y + m_positionY) * SCALE, m_gridSize * SCALE, m_gridSize * SCALE, {194, 178, 128, 255});
            else if (m_grid[x][y].value == 2)
                DrawRectangle((m_grid[x][y].x + m_positionX) * SCALE, (m_grid[x][y].y + m_positionY) * SCALE, m_gridSize * SCALE, m_gridSize * SCALE, BLACK);
            // printf("grid[%d][%d] = %d\n", x, y, grid[x][y]);
        }
    }
}

void FallingSand::SetCell(int posX, int PosY, int value)
{
    if (posX < 0 || posX >= m_columns || PosY < 0 || PosY >= m_rows)
        return;

    m_grid[posX][PosY].value = value;
}

int FallingSand::GetValueFromWroldPos(int worldX, int worldY)
{
    // Convert screen/world coordinates back to sand system's world units
    int scaledX = worldX / SCALE;
    int scaledY = worldY / SCALE;

    int gridX = (scaledX - m_positionX) / m_gridSize;
    int gridY = (scaledY - m_positionY) / m_gridSize;

    if (gridX < 0 || gridX >= m_columns || gridY < 0 || gridY >= m_rows)
        return -1; // Out of bounds

    return m_grid[gridX][gridY].value;
}

Vector2 FallingSand::GetCellPosFromWorld(int worldX, int worldY)
{
    // Convert screen/world coordinates back to sand system's world units
    int scaledX = worldX / SCALE;
    int scaledY = worldY / SCALE;

    int gridX = (scaledX - m_positionX) / m_gridSize;
    int gridY = (scaledY - m_positionY) / m_gridSize;

    if (gridX < 0 || gridX >= m_columns || gridY < 0 || gridY >= m_rows)
        return {Vector2(-1, -1)}; // Out of bounds

    return Vector2(gridX, gridY);
}