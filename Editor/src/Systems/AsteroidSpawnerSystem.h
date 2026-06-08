#pragma once
#include <ECS/SystemManager.h>
#include "ECS/Components.h"
#include "../SpriteSheet.h"

class AsteroidSpawnerSystem : public ISystem
{
public:
    AsteroidSpawnerSystem(Context& _context, int screenW, int screenH)
        : ISystem{ _context }, m_ScreenW(screenW), m_ScreenH(screenH) {
    }

    void Update(float dt) override;
    void SpawnAt(vec2 position, AsteroidTag::Size size, vec2 direction = { 0.0f, 0.0f });
    void Reset()
    {
        m_SpawnTimer = 0.0f;
        m_SpawnInterval = 2.0f; // back to starting difficulty
    }

private:
    float m_SpawnTimer = 0.0f;
    float m_SpawnInterval = 2.0f;
    int m_ScreenW, m_ScreenH;

    void SpawnAsteroid();
};