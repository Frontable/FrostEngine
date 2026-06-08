#include "DamageSystem.h"
#include "ECS/ECS.h"
#include "ECS/Components.h"

void DamageSystem::Update(float dt)
{
    auto& ecs = m_context.Get<FrostEngine::ECS>();
    auto& events = ecs.GetEvents();

    std::vector<Entity> toDestroy;

    auto alreadyQueued = [&](Entity e) {
        for (auto x : toDestroy) if (x == e) return true;
        return false;
        };

    for (auto& ev : events)
    {
        Entity a = ev.triggered;
        Entity b = ev.trigger;

        bool aIsBullet = ecs.HasComponent<BulletTag>(a);
        bool bIsBullet = ecs.HasComponent<BulletTag>(b);
        bool aIsAsteroid = ecs.HasComponent<AsteroidTag>(a);
        bool bIsAsteroid = ecs.HasComponent<AsteroidTag>(b);
        bool aIsPlayer = ecs.HasComponent<PlayerTag>(a);
        bool bIsPlayer = ecs.HasComponent<PlayerTag>(b);

        // Bullet <-> Asteroid
        if ((aIsBullet && bIsAsteroid) || (bIsBullet && aIsAsteroid))
        {
            Entity asteroid = aIsAsteroid ? a : b;
            Entity bullet = aIsBullet ? a : b;

            if (!alreadyQueued(asteroid) && !alreadyQueued(bullet))
            {
                auto& transform = ecs.GetComponent<Transform2D>(asteroid);
                auto& tag = ecs.GetComponent<AsteroidTag>(asteroid);
                auto& vel = ecs.GetComponent<Velocity2D>(asteroid);

                if (OnAsteroidDestroyed)
                    OnAsteroidDestroyed(transform.position, tag.size, vel.velocity);

                toDestroy.push_back(asteroid);
                toDestroy.push_back(bullet);
            }
        }

        // Player <-> Asteroid
        if ((aIsPlayer && bIsAsteroid) || (bIsPlayer && aIsAsteroid))
        {
            if (OnGameOver) OnGameOver();
            events.clear();
            return;
        }
    }

    for (Entity e : toDestroy)
        ecs.DeleteEntity(e);

    events.clear();
}