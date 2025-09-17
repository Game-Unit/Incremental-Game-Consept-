#include "Button.h"
#include "GameSetting.h"

#include <iostream>
#include <string>

#define SCALE GameSetting::Instance().GetGameScale()

Button::Button(const char *imagePath, Vector2 imagePosition, float scale)
{
    Image image = LoadImage(imagePath);
    m_image = image;

    int originalWidth = image.width;
    int originalHight = image.height;

    int newWidth = static_cast<int>(originalWidth * scale);
    int newHight = static_cast<int>(originalHight * scale);

    m_width = newWidth;
    m_hight = newHight;

    ImageResize(&image, newWidth, newHight);
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
    position = imagePosition;
}

Button::~Button()
{
    UnloadTexture(texture);
}

void Button::Draw()
{
    // Apply scale to position only
    Vector2 scaledPos = { position.x * SCALE, position.y * SCALE };
    
    // Draw the texture with scaled width/height
    DrawTexturePro(
        texture,
        Rectangle{ 0, 0, (float)texture.width, (float)texture.height },
        Rectangle{ scaledPos.x, scaledPos.y, texture.width * SCALE, texture.height * SCALE },
        Vector2{ 0, 0 },
        0.0f,
        WHITE
    );
}

bool Button::isPressed(Vector2 mousePos, bool mousePressed)
{
    Rectangle rect = {position.x * SCALE, position.y * SCALE, (float)texture.width * SCALE, (float)texture.height * SCALE};
    //DrawRectangleGradientEx(rect, RED, BLUE, GREEN, YELLOW); // For debugging, shows button area

    if (CheckCollisionPointRec(mousePos, rect) && mousePressed)
        return true;
    else
        return false;
}
