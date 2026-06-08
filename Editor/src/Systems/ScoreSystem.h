#pragma once
#include <ECS/SystemManager.h>

class ScoreSystem : public ISystem
{
public:
    ScoreSystem(Context& _context) : ISystem{ _context } {}

    // Call this when an asteroid is destroyed
    void AddScore(int points = 100) { m_Score += points; }

    int GetScore() const { return m_Score; }
    void Reset() { m_Score = 0; }

    void Update(float dt) override {} // score is event-driven, not tick-driven

private:
    int m_Score = 0;
};