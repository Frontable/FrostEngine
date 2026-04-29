#include "CollisionSystem.h"

void CollisionSystem::Update()
{
    for (auto &entity : m_entities)
    {
        auto &trans = m_ecs.GetComponent<Transform2D>(entity);
        auto &box = m_ecs.GetComponent<BoxCollider>(entity);

        box.rect.left = trans.position.x - trans.size.x / 2.0f;
        box.rect.top = trans.position.y - trans.size.y / 2.0f;
        box.rect.width = trans.size.x;
        box.rect.height = trans.size.y;
    }

    for (size_t i = 0; i < m_entities.size(); i++)
    {
        for (size_t j = i + 1; j < m_entities.size(); j++)
        {
            if (AABB(m_entities[i], m_entities[j]))
            {
                //std::cout << "Collision between entity "
                         // << m_entities[i] << " and " << m_entities[j] << "\n";

                m_ecs.RegisterEvent(m_entities[i], m_entities[j]);
            }
        }
    }
}

bool CollisionSystem::AABB(Entity a, Entity b)
{
    auto& A = m_ecs.GetComponent<BoxCollider>(a).rect;
    auto& B = m_ecs.GetComponent<BoxCollider>(b).rect;

    bool result =
        A.left < B.right() &&
        A.right() > B.left &&
        A.top < B.bottom() &&
        A.bottom() > B.top;

    // if (result)
    // {
    //     std::cout << "Collision:\n";

    //     std::cout << "A: left=" << A.left
    //               << " right=" << A.right()
    //               << " top=" << A.top
    //               << " bottom=" << A.bottom()
    //               << "\n";

    //     std::cout << "B: left=" << B.left
    //               << " right=" << B.right()
    //               << " top=" << B.top
    //               << " bottom=" << B.bottom()
    //               << "\n";
    // }

    return result;
}