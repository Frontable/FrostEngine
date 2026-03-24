#pragma once
#include "Platform/Event.h"
#include <vector>

namespace FrostEngine
{
    class EventQueue
    {
    public:
      void Push(const Event& e) { m_events.emplace_back(e); }
      void Clear() { m_events.clear(); }
      
      const std::vector<Event>& Events() const { return m_events; }
    
    private:

    std::vector<Event> m_events;
    
    };

}