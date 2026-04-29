#include "Input.h"

GLFWwindow* Input::m_Window = nullptr;

std::array<bool, GLFW_KEY_LAST + 1> Input::m_Keys{};
std::array<bool, GLFW_KEY_LAST + 1> Input::m_KeysJustPressed{};
std::array<bool, GLFW_KEY_LAST + 1> Input::m_KeysJustReleased{};

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key < 0 || key > GLFW_KEY_LAST)
        return;

    if (action == GLFW_PRESS)
    {
        m_Keys[key] = true;
        m_KeysJustPressed[key] = true;
    }
    else if (action == GLFW_RELEASE)
    {
        m_Keys[key] = false;
        m_KeysJustReleased[key] = true;
    }
}

void Input::Update()
{
    m_KeysJustPressed.fill(false);
    m_KeysJustReleased.fill(false);
}

bool Input::IsKeyPressed(int key)
{
    return m_Keys[key];
}

bool Input::IsKeyJustPressed(int key)
{
    return m_KeysJustPressed[key] && !m_KeysJustReleased[key];
}

bool Input::IsKeyJustReleased(int key)
{
    return !m_KeysJustPressed[key] && m_KeysJustReleased[key];
}