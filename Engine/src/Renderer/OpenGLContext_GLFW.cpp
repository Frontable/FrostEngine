#include "Renderer/OpenGLContext.h"
#include "Platform/Window.h"
#include "Core/Logger.h"
#include "glad/glad.h"
#include "glfw/glfw3.h"

namespace FrostEngine
{
    bool OpenGLContext::Init(Window& window)
    {
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            FROST_ERROR("Failed to init glad");
            return false;
        }

        glViewport(0, 0, window.Width(), window.Height());
        return true;
    }
}