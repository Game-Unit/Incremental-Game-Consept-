#include "Worker.h"
#include "GameSetting.h"
#include "Money.h"

#include <cmath>

#define SCALE GameSetting::Instance().GetGameScale()

Worker::Worker(Vector2 startPos, std::vector<Vector2> positionsToGo)
    : m_position(startPos), m_positionsToGo(positionsToGo), m_anim(3, 0.5f)
{
    m_texture = LoadTexture("Sprites/Worker-Sheet.png");
}

Worker::~Worker()
{
    UnloadTexture(m_texture);
}

void Worker::Render(FallingSand& fallingSand)
{
    m_anim.Update(GetFrameTime());

    // Frame size (assuming frames are arranged horizontally in the sprite sheet)
    int frameWidth = m_texture.width / 3;
    int frameHeight = m_texture.height;

    Rectangle sourceRec = {
        (float)(m_anim.GetFrame() * frameWidth),            // x position in spritesheet
        0.0f,                                               // y position
        m_forward ? (float)frameWidth : -(float)frameWidth, // width
        (float)frameHeight                                  // height
    };

    Rectangle destRec = {
        m_position.x * SCALE, m_position.y * SCALE,
        (float)frameWidth * 0.4f * SCALE,
        (float)frameHeight * 0.4f * SCALE};

    Vector2 origin = {0, 0}; // draw from top-left corner

    DrawTexturePro(m_texture, sourceRec, destRec, origin, 0.0f, WHITE);

    int amountOfSandDisplayed = 0;
    for (int y = 0; y > -20; y--)
    {
        for (int x = 0; x < 2; x++)
        {
            float posX = (x + m_position.x + (m_forward ? 7.5f : 3.5f)) * SCALE;
            float posY = (y + m_position.y + 6.5f) * SCALE;

            if (m_currentSandHold >= 1)
                DrawRectangle(posX, posY, 1 * SCALE, 1 * SCALE, {194, 178, 128, 255});

            amountOfSandDisplayed++;
            if (amountOfSandDisplayed > m_currentSandHold + 1)
                return;
        }
    }
}

void Worker::Update(FallingSand &fallingSand)
{
    if (m_positionsToGo.empty())
        return;

    for (int x = 0; x < 10; x++)
    {
        if (m_currentSandHold >= m_maxSandHold)
            break;

        for (int y = 0; y < 15; y++)
        {
            if (!(m_currentSandHold >= m_maxSandHold))
            {
                float posX = (x + m_position.x + 5) * SCALE;
                float posY = (y + m_position.y) * SCALE;

                if (fallingSand.GetValueFromWroldPos((int)posX, (int)posY) == 1)
                {
                    int cellX = (int)(fallingSand.GetCellPosFromWorld((int)posX, (int)posY).x);
                    int cellY = (int)(fallingSand.GetCellPosFromWorld((int)posX, (int)posY).y);

                    fallingSand.SetCell(cellX, cellY, 0);

                    m_currentSandHold++;
                    if (m_currentSandHold >= m_maxSandHold)
                        break;
                }
            }
        }
    }

    Vector2 target = m_positionsToGo[m_currentIndex];
    Vector2 direction = {target.x - m_position.x, target.y - m_position.y};
    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance < 1.0f)
    {
        if (target.x == m_positionsToGo[0].x && target.y == m_positionsToGo[0].y)
        {
            Money::Add(m_currentSandHold * Money::GetCurrentSandValue());
            m_currentSandHold = 0;
        }

        if (m_forward)
        {
            m_currentIndex++;
            if (m_currentIndex >= static_cast<int>(m_positionsToGo.size()))
            {
                m_currentIndex = static_cast<int>(m_positionsToGo.size()) - 2; // step back
                m_forward = false;
            }
        }
        else
        {
            m_currentIndex--;
            if (m_currentIndex < 0)
            {
                m_currentIndex = 1; // step forward
                m_forward = true;
            }
        }
    }
    else
    {
        direction.x /= distance;
        direction.y /= distance;

        m_speed = 20.0f; // units per second
        m_position.x += direction.x * m_speed * GetFrameTime();
        m_position.y += direction.y * m_speed * GetFrameTime();
    }
}