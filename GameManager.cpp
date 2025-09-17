#include "GameManager.h"

std::vector<std::unique_ptr<Worker>> GameManager::m_workers;
std::vector<Vector2> GameManager::m_workerWalkPoints;

GameManager::GameManager()
{
    m_workerWalkPoints.push_back(Vector2{-25, 87});
    m_workerWalkPoints.push_back(Vector2{36, 87});
    m_workerWalkPoints.push_back(Vector2{36, 136});
    m_workerWalkPoints.push_back(Vector2{110, 136});

    m_workers.push_back(std::make_unique<Worker>(Vector2{-25, 87}, m_workerWalkPoints));
}

void GameManager::AddWorker()
{
    m_workers.push_back(std::make_unique<Worker>(Vector2{-25, 87}, m_workerWalkPoints));
}

void GameManager::Update(FallingSand& sandSystem)
{
    for (auto &worker : m_workers)
    {
        worker->Render(sandSystem);
        worker->Update(sandSystem);
    }
}