#pragma once
#include <GLFW/glfw3.h>

class Window {
public:
    Window(int w, int h, const char* t);
    ~Window();
    GLFWwindow* Get() const noexcept;
    void PollEvents() noexcept;
    void SwapBuffers() noexcept;
    bool ShouldClose() const noexcept;

private:
    GLFWwindow* handle{nullptr};
    int width{0}, height{0};
    const char* title{nullptr};
};
