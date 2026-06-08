#pragma once
#include <ECS/SystemManager.h>


class MovementSystem : public ISystem
{
    public:
    MovementSystem(Context& _context):ISystem{_context}{}
    
    void Update(float dt) override;    

};


