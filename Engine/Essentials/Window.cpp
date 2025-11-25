





#include "Window.h"
#include <Logger/Logger.h>
#include <stdexcept>

Window::Window(int w, int h, const char* t) : width(w), height(h), title(t) {
    if (!glfwInit()) {
        FROST_ERROR("glfwInit() failed");
        throw std::runtime_error("Failed to init GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!handle) {
        FROST_ERROR("Failed to create GLFW window: {%s} ({%d}x{%d})", title, width, height);
        glfwTerminate();
        throw std::runtime_error("Failed to create window");
    }
    glfwMakeContextCurrent(handle);
    FROST_LOG("Window created: {%s} ({%d}x{%d})", title, width, height);
}

Window::~Window() {
    if (handle) {
        glfwDestroyWindow(handle);
        handle = nullptr;
        FROST_LOG("Window destroyed");
    }
    glfwTerminate();
}

GLFWwindow* Window::Get() const noexcept { return handle; }
void Window::PollEvents() noexcept { glfwPollEvents(); }
void Window::SwapBuffers() noexcept { if (handle) glfwSwapBuffers(handle); }
bool Window::ShouldClose() const noexcept { return handle ? glfwWindowShouldClose(handle) : true; }
