#pragma once

#include <GLFW/glfw3.h>
#include <array>

class Input
{
public:
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void Update();
    static bool IsKeyPressed(int key);
    static bool IsKeyJustPressed(int key);
    static bool IsKeyJustReleased(int key);

private:
    static GLFWwindow* m_Window;

    static std::array<bool, GLFW_KEY_LAST + 1> m_Keys;
    static std::array<bool, GLFW_KEY_LAST + 1> m_KeysJustPressed;
    static std::array<bool, GLFW_KEY_LAST + 1> m_KeysJustReleased;
};