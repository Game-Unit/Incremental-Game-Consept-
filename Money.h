#include "raylib.h"

#include <stdio.h>
#include <iostream>
#include <string>

#pragma once

class Money
{
private:
    static unsigned long int m_currentMoney;

    std::string m_text;

    static int m_currentSandValue;

public:
    static void Add(int amount);
    static void Remove(int amount);
    static unsigned long int GetCurrentMoney() { return m_currentMoney; }
    static int GetCurrentSandValue() { return m_currentSandValue; }
    static void SetCurrentSandValue(int value) { m_currentSandValue = value; }

    void Update();
};