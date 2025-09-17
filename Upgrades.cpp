#include "Upgrades.h"
#include "Building.h"
#include "Building.h"
#include "raylib.h"
#include "raygui.h"
#include "GameManager.h"
#include "Money.h"

void MoneyBuildingsUpgrades::ShowUpgrades(Building& building)
{
    std::string text = "Add Worker (" + std::to_string(m_upgradePrice) + ")";

    GuiGroupBox({0, 100, 300, 500}, "Money Buildings Upgrades");

    GuiSetStyle(LABEL, TEXT_COLOR_NORMAL, 0xFFFFFFFF);
    GuiLabel({10, 120, 220, 50}, text.c_str());
    if (GuiButton({240, 120, 50, 50}, "+") && static_cast<int>(Money::GetCurrentMoney()) >= m_upgradePrice)
    {
        GameManager::AddWorker();
        Money::Remove(m_upgradePrice);
    }

    GuiLabel({10, 190, 220, 50}, "sand price (100)");
    if (GuiButton({240, 190, 50, 50}, "+") && static_cast<int>(Money::GetCurrentMoney()) >= 100)
    {
        Money::SetCurrentSandValue(Money::GetCurrentSandValue() + 1);
        Money::Remove(100);
    }
}