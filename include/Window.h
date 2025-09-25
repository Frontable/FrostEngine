







#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Window
{
    public:
    Window(int width, int height, const char* title);
    ~Window();

    GLFWwindow* GetNativeWindow() const;

    void PollEvents();
    void SwapBuffers();
    bool ShouldClose();

    private:

    GLFWwindow* m_window;
};