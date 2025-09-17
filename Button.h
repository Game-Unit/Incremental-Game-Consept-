#pragma once
#include "raylib.h"

class Button
{
    public:
        Button(const char* imagePath, Vector2 imagePosition, float scale);
        ~Button();
        void Draw();
        bool isPressed(Vector2 mousePos, bool mousePressed);

        int m_width;
        int m_hight;

        Image m_image;

    private:
        Texture2D texture;
        Vector2 position;
};