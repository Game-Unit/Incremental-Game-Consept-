#include "GameSetting.h"
#include "Building.h"
#include "raylib.h"

#pragma once

#define SCALE GameSetting::Instance().GetGameScale()

class UpgradeMenu
{
protected:
    Vector2 m_position;
    int m_upgradePrice = 10;
    
public:
    virtual void ShowUpgrades(Building& building) = 0;
};