#include "AsteroidSpawnerSystem.h"
#include "ECS/ECS.h"
#include "ECS/Components.h"
#include "FrostMath.h"
#include <cstdlib>
#include <cmath>

void AsteroidSpawnerSystem::Update(float dt)
{
    m_SpawnTimer += dt;
    if (m_SpawnTimer >= m_SpawnInterval)
    {
        m_SpawnTimer = 0.0f;
        SpawnAsteroid();
        if (m_SpawnInterval > 0.5f)
            m_SpawnInterval -= 0.05f;
    }
}

void AsteroidSpawnerSystem::SpawnAsteroid()
{
    int edge = rand() % 4;
    vec2 spawnPos{};

    switch (edge)
    {
    case 0: spawnPos = { (float)(rand() % m_ScreenW), -80.0f };             break;
    case 1: spawnPos = { (float)(rand() % m_ScreenW), m_ScreenH + 80.0f }; break;
    case 2: spawnPos = { -80.0f, (float)(rand() % m_ScreenH) };             break;
    case 3: spawnPos = { m_ScreenW + 80.0f, (float)(rand() % m_ScreenH) }; break;
    }

    SpawnAt(spawnPos, AsteroidTag::Size::Large);
}

void AsteroidSpawnerSystem::SpawnAt(vec2 position, AsteroidTag::Size size, vec2 direction)
{
    auto& ecs = m_context.Get<FrostEngine::ECS>();

    float scale, radius, speed;
    switch (size)
    {
    case AsteroidTag::Size::Large:
        scale = 60.0f; radius = 28.0f; speed = 80.0f + rand() % 80; break;
    case AsteroidTag::Size::Medium:
        scale = 35.0f; radius = 16.0f; speed = 120.0f + rand() % 80; break;
    case AsteroidTag::Size::Small:
        scale = 20.0f; radius = 9.0f;  speed = 160.0f + rand() % 80; break;
    }

    // If no direction provided pick a random one
    if (direction.x == 0.0f && direction.y == 0.0f)
    {
        float angle = ((float)(rand() % 360)) * (PI / 180.0f);
        direction = { cos(angle), sin(angle) };
    }

    // Normalize direction
    float len = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (len > 0.0f) { direction.x /= len; direction.y /= len; }

    float angularVel = ((rand() % 200) - 100) / 100.0f;

    Sprite sprite;
    switch (size)
    {
    case AsteroidTag::Size::Large:  sprite = GetSprite(SpriteID::ASTEROID_LARGE); break;
    case AsteroidTag::Size::Medium: sprite = GetRandomMediumAsteroid();            break;
    case AsteroidTag::Size::Small:  sprite = GetRandomSmallAsteroid();             break;
    }

    Entity asteroid = ecs.CreateEntity();

    ecs.AddComponent<Transform2D>(asteroid, {
        position, 0.0f, { scale, scale }
        });
    ecs.AddComponent<Velocity2D>(asteroid, {
        { direction.x * speed, direction.y * speed }, angularVel
        });
    ecs.AddComponent<Sprite>(asteroid, sprite);
    ecs.AddComponent<CircleCollider>(asteroid, { radius });
    ecs.AddComponent<AsteroidTag>(asteroid, { size });
    ecs.AddComponent<SpawnImmunity>(asteroid, { 0.3f });
}