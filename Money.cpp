#include "raygui.h"
#include "Money.h"
#include "GameSetting.h"

#define SCALE GameSetting::Instance().GetGameScale()

unsigned long int Money::m_currentMoney = 0;
int Money::m_currentSandValue = 1;

void Money::Add(int amount)
{
    m_currentMoney += amount;
}

void Money::Remove(int amount)
{
    m_currentMoney -= amount;
}

void Money::Update()
{
    std::string text = "Money: " + std::to_string(m_currentMoney);

    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    GuiSetStyle(LABEL, TEXT_COLOR_NORMAL, 0x008000FF); // Green color
    GuiLabel({5, 5, 400, 100}, text.c_str());
}