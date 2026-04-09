
#include "Window.h"
#include <iostream>


namespace FROST_RENDERING
{

    Window::Window(const char *_title, int _width, int _height)
    {

        if (!glfwInit())
        {
            printf("Failed to init glfw!\n");
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
            printf("Failed to create GLFW window!\n");
        }
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, this);
        glfwSetWindowSizeCallback(m_Window, glfwWindowResize);
        //glfwSetWindowCloseCallback()
    }    

    void glfwWindowResize(GLFWwindow *window, int _w, int _h)
    {
        Window *win = static_cast<Window *>(glfwGetWindowUserPointer(window));
        win->m_Width = _w;
        win->m_Height = _h;

        glViewport(0, 0, _w, _h);
    }

    void glfwCloseCallback(GLFWwindow *_window)
    {
        if(glfwWindowShouldClose(_window))
        {

        }
    }

}
