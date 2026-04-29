#pragma once
#include "glad/glad.h"
#include "glfw/glfw3.h"

namespace FROST_RENDERING
{

    class Window
    {
        public:
        Window():Window("default", 640, 480){};
        Window(const char* title, int _width, int _height);
        
        int Width() const { return m_Width; }
        int Height() const { return m_Height; }

        GLFWwindow* Handle() const { return m_Window; }

        void PollEvents() { glfwPollEvents(); }
        void SwapBuffers() { glfwSwapBuffers(m_Window); }

        private:
        GLFWwindow* m_Window;
        const char* m_Title;
        int m_Width{0};
        int m_Height{0};

        friend void glfwWindowResize(GLFWwindow* _window, int _w, int _h);
        //friend void glfwKeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);

    };

}