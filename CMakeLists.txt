




cmake_minimum_required(VERSION 3.10)

project("Engine")

include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
)
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
)

FetchContent_MakeAvailable(glfw glm)

add_library(glad STATIC dependencies/glad/src/glad.c)
target_include_directories(glad PUBLIC dependencies/glad/include)

aux_source_directory(src SOURCES)
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32.lib)
endif()

#Copying the shaders to binary folder so I don't have to use my absolute path.
file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE 
${glfw_SOURCE_DIR}/include
${glm_SOURCE_DIR}
include
)
