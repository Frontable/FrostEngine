




#pragma once
#include "Window.h"

static bool s_Keys[1024];

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS)
            s_Keys[key] = true;
        else if (action == GLFW_RELEASE)
            s_Keys[key] = false;
    }
}

class Input
{
    public:

    static void Init(GLFWwindow* window);

    static bool IsKeyPressed(int key);

    private:
    static GLFWwindow* m_window;

};
