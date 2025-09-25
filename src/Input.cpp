




#include "Input.h"
#include <iostream>

GLFWwindow* Input::m_window = nullptr;


void Input::Init(GLFWwindow* window)
{
    m_window = window;
    glfwSetKeyCallback(window, KeyCallback);
}

bool Input::IsKeyPressed(int key)
{
    return s_Keys[key];
}
