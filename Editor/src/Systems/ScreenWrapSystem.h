#pragma once
#include <ECS/SystemManager.h>

class ScreenWrapSystem : public ISystem
{
public:
    ScreenWrapSystem(Context& _context, int screenW, int screenH)
        : ISystem{ _context }, m_ScreenW(screenW), m_ScreenH(screenH) {
    }

    void Update(float dt) override;

private:
    int m_ScreenW, m_ScreenH;
};