cmake_minimum_required(VERSION 3.17)
project(FrostEngine LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/build/_deps")

# --- Dependencies ---
add_subdirectory(dependencies)

# --- Engine ---
add_subdirectory(Engine)

# --- Asteroids ---
add_subdirectory(Asteroids)