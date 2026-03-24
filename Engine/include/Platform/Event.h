#pragma once

namespace FrostEngine
{
    enum class EventType
    {
        None = 0,
        WindowClose,
        KeyDown,
        KeyUp,
        MouseMove,
    };

    struct Event
    {
        EventType type = EventType::None;
        union
        {
            struct { int key; } key;
            struct { float x, y; } mouse;
        };
    };
}