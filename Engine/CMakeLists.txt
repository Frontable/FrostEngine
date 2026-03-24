

project(Engine)

add_library(Engine STATIC
    src/Application.cpp

    src/Core/Logger.cpp
    src/Core/Time.cpp
    #src/Core/Config.cpp

    src/Platform/Window_GLFW.cpp
    #src/Platform/Event.cpp

    #src/Input/Input_GLFW.cpp

    src/Renderer/OpenGLContext_GLFW.cpp
    src/Renderer/Shader.cpp
    src/Renderer/Renderer_GL.cpp
    src/Renderer/Renderer.cpp
    src/Renderer/RendererPrimitives.cpp

    src/Resources/ResourceManager.cpp

)

target_include_directories(Engine PUBLIC include)

# Warnings (optional but recommended)
if(MSVC)
    target_compile_options(Engine PRIVATE /W4)
else()
    target_compile_options(Engine PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_link_libraries(Engine PUBLIC glfw glad stb_image)

#[[
cmake_minimum_required(VERSION 3.20)

add_library(Engine STATIC)


file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Core/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Renderer/*.cpp"
)

file(GLOB_RECURSE ENGINE_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/Engine/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/Engine/Core/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/Engine/Platform/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/Engine/Renderer/*.h"
)

target_sources(Engine PRIVATE ${ENGINE_SOURCES} ${ENGINE_HEADERS})

target_include_directories(Engine
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(Engine
    PUBLIC
        glm
        glfw
        glad
)
#]]