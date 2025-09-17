#include "UpgradeMenu.h"
#include "raylib.h"
#include "Worker.h"
#include "Building.h"

#include <vector>
#include <memory>

#pragma once

class MoneyBuildingsUpgrades : public UpgradeMenu
{
private:
    
public:
    virtual void ShowUpgrades(Building& building) override;
};