






#include "Window.h"
#include <stdexcept>
#include <iostream>


Window::Window(int width, int height, const char* title)
{
    this->m_window = glfwCreateWindow(width, height, title, NULL, NULL);
    if(!this->m_window)
    {
        throw std::runtime_error("Failed to create window!");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwMakeContextCurrent(this->m_window);     

}

Window::~Window()
{
    glfwDestroyWindow(this->m_window);
}

GLFWwindow* Window::GetNativeWindow() const
{
    return this->m_window;
}

void Window::PollEvents()
{
    glfwPollEvents();
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(this->m_window);
}

bool Window::ShouldClose()
{   
    return glfwWindowShouldClose(this->m_window);
}