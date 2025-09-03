




cmake_minimum_required(VERSION 3.10)

project("Breakout")

include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
)

FetchContent_MakeAvailable(glfw)

add_library(glad STATIC dependencies/glad/src/glad.c)
target_include_directories(glad PUBLIC dependencies/glad/include)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad)

if (WIN32)
    target_link_libraries(Breakout PRIVATE opengl32.lib)
endif()

# Include GLFW headers
target_include_directories(Breakout PRIVATE 
${glfw_SOURCE_DIR}/include
${glad_SOURCE_DIR/include}
)