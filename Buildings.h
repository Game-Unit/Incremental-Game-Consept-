#include "Building.h"
#include "Animation.h"
#include "raylib.h"
#include "GameSetting.h"
#include "Money.h"

#define SCALE GameSetting::Instance().GetGameScale()

class Mine : public Building
{
private:
    int produtionRate = 1;
    Animation anim;
    Texture2D texture;

    float m_SpawnItem;

public:
    Mine(Vector2 position) : Building(position), anim(2, 0.1f) 
    {
        texture = LoadTexture("Sprites/mianing mashen-Sheet.png");
    }

    ~Mine() { UnloadTexture(texture); };

    virtual void Upgrade() override
    {
        m_currentLevel++;
    }
    virtual void Render() override
    {
        anim.Update(GetFrameTime());

        // Frame size (assuming frames are arranged horizontally in the sprite sheet)
        int frameWidth = texture.width / 2;
        int frameHeight = texture.height;

        Rectangle sourceRec = {
            (float)(anim.GetFrame() * frameWidth), // x position in spritesheet
            0.0f,                                  // y position
            (float)frameWidth,                     // width
            (float)frameHeight                     // height
        };

        Rectangle destRec = {
            m_position.x * SCALE, m_position.y * SCALE,
            (float)frameWidth * 1.5f * SCALE, 
            (float)frameHeight * 1.5f * SCALE
        };

        Vector2 origin = {0, 0}; // draw from top-left corner

        DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, WHITE);
    }

    virtual void Tick(FallingSand& sandSystem) override
    {
        m_SpawnItem += GetFrameTime();

        if (m_SpawnItem >= 1.0f / produtionRate)
        {
            sandSystem.SetCell(78, 5);
            m_SpawnItem = 0.0f;
        }
    }
};

class MoneyBuilding : public Building
{
private:
    int produtionRate = 1;
    Texture2D texture;

public:

    MoneyBuilding(Vector2 position) : Building(position)
    { 
        texture = LoadTexture("Sprites/Money Building.png");
        m_maxLevel = 5;
    }

    ~MoneyBuilding() { UnloadTexture(texture); };

    virtual void Upgrade() override
    {
        if (m_currentLevel == m_maxLevel)
            return;
        m_currentLevel++;

        switch (m_currentLevel)
        {
        case 1:
            Money::SetCurrentSandValue(2);
            break;
        case 2:
            Money::SetCurrentSandValue(3);
            break;
        case 3:
            Money::SetCurrentSandValue(4);
            break;
        case 4:
            Money::SetCurrentSandValue(5);
            break;
        case 5:
            Money::SetCurrentSandValue(6);
            break;
        default:
            break;
        }
    }
    virtual void Render() override
    {
        DrawTextureEx(texture, {m_position.x * SCALE, m_position.y * SCALE}, 0.0f, 1.5f * SCALE, WHITE);
    }

    virtual void Tick(FallingSand& sandSystem) override
    {
        
    }
};