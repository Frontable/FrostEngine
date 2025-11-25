




cmake_minimum_required(VERSION 3.20)

add_library(Engine STATIC)


file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Essentials/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Logger/*.cpp"
)

file(GLOB_RECURSE ENGINE_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Essentials/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Logger/*.h"
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
        stb_image
        imgui
)
