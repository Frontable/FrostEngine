#pragma once
#include <ECS/SystemManager.h>


class PlayerSystem : public ISystem
{
    public:
    PlayerSystem(Context& _context):ISystem{_context}{}
    
    void Update(float dt) override;

};