#define RAYGUI_IMPLEMENTATION
#include "raylib.h"
#include "raygui.h"
#include "GameSetting.h"
#include "GameCamera.h"
#include "Building.h"
#include "Buildings.h"
#include "FallingSand.h"
#include "Worker.h"
#include "Money.h"
#include "Button.h"
#include "UpgradeMenu.h"
#include "Upgrades.h"
#include "GameManager.h"

#include <vector>
#include <memory>
#include <cstdio>

#define SCALE GameSetting::Instance().GetGameScale()

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(1600, 900, "Falling Sand Game");

    GameSetting::Instance().ChangeGameScale();

    GameCamera camera = {};

    std::vector<std::unique_ptr<Building>> buildings;

    buildings.push_back(std::make_unique<Mine>(Vector2{120, 53}));
    buildings.push_back(std::make_unique<MoneyBuilding>(Vector2{-50, 53}));

    FallingSand sandSystem(8.3 * SCALE, 15 * SCALE, 15.8 * SCALE, 14.8 * SCALE);

    std::vector<std::unique_ptr<UpgradeMenu>> upgradeMenu;

    upgradeMenu.push_back(std::make_unique<MoneyBuildingsUpgrades>());

    Money money = {};

    Button moneyBuildingButton = {"Sprites/Blank.png", Vector2{-50, 53}, 1.5f};

    GameManager gameManager = {};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        if (IsWindowResized())
        {
            GameSetting::Instance().ChangeGameScale();
        }

        camera.Tick();

        BeginMode2D(camera.GetCamera());

        DrawRectangle((int)(-1000 * SCALE), (int)(100 * SCALE), 1040 * SCALE, 1 * SCALE, WHITE);
        DrawRectangle((int)(120 * SCALE), (int)(100 * SCALE), 47 * SCALE, 1 * SCALE, WHITE);

        DrawRectangle((int)(40 * SCALE), (int)(100 * SCALE), 1 * SCALE, 49 * SCALE, WHITE);
        DrawRectangle((int)(120 * SCALE), (int)(100 * SCALE), 1 * SCALE, 49 * SCALE, WHITE);

        DrawRectangle((int)(166 * SCALE), (int)(0 * SCALE), 1 * SCALE, 100 * SCALE, WHITE);
        DrawRectangle((int)(166 * SCALE), (int)(0 * SCALE), 1040 * SCALE, 1 * SCALE, WHITE);

        DrawRectangle((int)(40 * SCALE), (int)(149 * SCALE), 81 * SCALE, 1 * SCALE, WHITE);

        for (auto &building : buildings)
        {
            building->Render();
            building->Tick(sandSystem);
        }

        sandSystem.Update();

        gameManager.Update(sandSystem);

        moneyBuildingButton.Draw();
        
        if (IsMouseButtonPressed(0))
        {
            Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), camera.GetCamera());
            if (moneyBuildingButton.isPressed(mousePos, true))
            {
                std::printf("Money Button Pressed\n");
            }
        }

        EndMode2D();

        money.Update();

        for (auto& menu : upgradeMenu)
        {
            menu->ShowUpgrades(*buildings[1]);
        }

        EndDrawing();
    }
}