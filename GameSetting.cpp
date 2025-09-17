#include "GameSetting.h"

void GameSetting::ChangeGameScale()
{
    m_scaleX = (float)GetScreenWidth() / baseWidth;
    m_scaleY = (float)GetScreenHeight() / baseHeight;
        m_gameScale = (m_scaleX < m_scaleY) ? m_scaleX : m_scaleY;
}