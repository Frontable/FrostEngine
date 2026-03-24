

#include "Platform/Window.h"
#include "glfw/glfw3.h"
#include "Core/Logger.h"

namespace FrostEngine
{
    static void GLFW_ErrorCallback(int code, const char *desc)
    {
        FROST_ERROR("GLFW error" + std::to_string(code) + " : " + (desc ? desc : ""));
    }
    static void GLFW_WindowCloseCallback(GLFWwindow *)
    {
    }
    static void GLFW_KeyCallback(GLFWwindow* win, int key, int, int action, int)
    {
        Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
        if(!window) return;
        Event e{};
        e.key.key = key;
        if(action == GLFW_PRESS)
            e.type = EventType::KeyDown;
        else if(action == GLFW_RELEASE)
            e.type = EventType::KeyUp;
        else
            return;
        //std::cout<< "Event: " << action << " key " << key << std::endl;
        window->Events().Push(e);
    }
    Window::Window()
    {
        glfwSetErrorCallback(GLFW_ErrorCallback);
        if (!glfwInit())
        {
            FROST_ERROR("Failed to init GLFW");
        }
    }
    Window::~Window()
    {
        if (m_window)
        {
            glfwDestroyWindow(static_cast<GLFWwindow *>(m_window));
            m_window = nullptr;
        }
        glfwTerminate();
    }

    bool Window::Create(int width, int height, const char *name)
    {
        m_width = width;
        m_height = height;
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow *win = glfwCreateWindow(m_width, m_height, name, nullptr, nullptr);
        if (!win)
        {
            FROST_ERROR("Failed to create GLFW window");
            return false;
        }
        m_window = win;

        glfwSetWindowCloseCallback(win, GLFW_WindowCloseCallback);
        glfwSetWindowUserPointer(win, this);
        glfwSetKeyCallback(win, GLFW_KeyCallback);
        glfwMakeContextCurrent(win);
        //glfwSwapInterval(1); // VSync on by default;

        return true;
    }

    void Window::PollEvents()
    {
        m_events.Clear();
        glfwPollEvents();

        GLFWwindow *win = static_cast<GLFWwindow *>(m_window);
        if (!win)
            return;
        if (glfwWindowShouldClose(win))
        {
            m_open = false;
            Event e{};
            e.type = EventType::WindowClose;
            m_events.Push(e);
        }      

        int w, h;
        glfwGetFramebufferSize(win, &w, &h);
        m_width = w;
        m_height = h;
    }

    void Window::SwapBuffers()
    {
        GLFWwindow *win = static_cast<GLFWwindow *>(m_window);
        if (!win)
            return;
        glfwSwapBuffers(win);
    }

    void Window::SetVSync(bool vsync)
    {
        glfwSwapInterval(vsync);
    }

    
    EventQueue& Window::Events()
    {
        return m_events;
    }

    bool Window::IsOpen() const { return m_open; }
    int Window::Width() const { return m_width; }
    int Window::Height() const { return m_height; }

    void *Window::Handle() const { return m_window; }

}