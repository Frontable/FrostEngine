#pragma once
#include "Platform/EventQueue.h"

namespace FrostEngine
{
    class Window
    {
    public:
        Window();
        ~Window();

        bool Create(int width, int height, const char* name);
        void PollEvents();
        void SwapBuffers();

        bool IsOpen() const;
        int Width() const;
        int Height() const;

        void* Handle() const;

        void SetVSync(bool vsync);
        EventQueue& Events();
    private:
        void* m_window = nullptr;
        bool m_open = true;
        int m_width = 0;
        int m_height = 0;
        EventQueue m_events;
    };
}