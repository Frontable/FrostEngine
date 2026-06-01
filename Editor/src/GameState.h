#pragma once
#include "ECS/ECS.h"
#include <vector>

class GameState
{




    private:
    Entity player;
    std::vector<Entity> asteroids;
    std::vector<Entity> bullets;
};