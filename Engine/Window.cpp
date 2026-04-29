
#include "Window.h"
#include <iostream>
#include "Logger/Logger.h"
#include "Input.h"


namespace FROST_RENDERING
{

    Window::Window(const char *_title, int _width, int _height)
    {

        if (!glfwInit())
        {
            FROST_ERROR("Failed to initialize GLFW!");
        }

        m_Title = _title;
        m_Width = _width;
        m_Height = _height;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);
        if (!m_Window)
        {
            FROST_ERROR("Failed to create GLFW Window!");
        }
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, this);
        glfwSetWindowSizeCallback(m_Window, glfwWindowResize);
        glfwSetKeyCallback(m_Window, Input::KeyCallback);
        //glfwSetWindowCloseCallback()
    }    

    void glfwWindowResize(GLFWwindow *window, int _w, int _h)
    {
        Window *win = static_cast<Window *>(glfwGetWindowUserPointer(window));
        win->m_Width = _w;
        win->m_Height = _h;

        glViewport(0, 0, _w, _h);
    }
}
