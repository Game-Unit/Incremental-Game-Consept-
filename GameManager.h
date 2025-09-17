#include "Worker.h"
#include "raylib.h"
#include "FallingSand.h"

#include <vector>
#include <memory>

#pragma once

class GameManager
{
private:
    static std::vector<std::unique_ptr<Worker>> m_workers;
    static std::vector<Vector2> m_workerWalkPoints;

public:
    GameManager();

    static void AddWorker();

    void Update(FallingSand& sandSystem);
};