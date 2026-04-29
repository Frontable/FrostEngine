

project(Editor)

add_executable(Editor 
    main.cpp
    src/Editor.cpp

)

target_include_directories(Editor PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}
)


target_link_libraries(Editor PUBLIC Engine glfw glad stb_image)





