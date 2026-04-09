

project(Engine)

add_library(Engine 
    Application.cpp
    Window.cpp
    Rendering/Essentials/Shader.cpp
    Rendering/Essentials/ShaderLoader.cpp
    Rendering/Essentials/Texture.cpp
    Rendering/Essentials/TextureLoader.cpp
    Rendering/Core/Camera2D.cpp

)

target_include_directories(Engine PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}
)


target_link_libraries(Engine PUBLIC glfw glad stb_image)