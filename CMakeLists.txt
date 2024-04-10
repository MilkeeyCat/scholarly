cmake_minimum_required(VERSION 3.27)
project(NoName)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(IMGUI_SOURCES
    dependencies/imgui/imgui.cpp
    dependencies/imgui/imgui_draw.cpp
    dependencies/imgui/imgui_tables.cpp
    dependencies/imgui/imgui_widgets.cpp

    dependencies/imgui/backends/imgui_impl_glfw.cpp
    dependencies/imgui/backends/imgui_impl_opengl3.cpp
)

file(GLOB_RECURSE SOURCES
    src/*.h
    src/*.cpp
)

list(APPEND SOURCES ${IMGUI_SOURCES})

add_executable(scholarly ${SOURCES})

set(GLFW_BUILD_WAYLAND OFF)

add_subdirectory(dependencies/glfw)
include_directories(dependencies/glfw/include)

set(SKIP_BUILD_TEST on)
set(BUILD_DOC off)
add_subdirectory(dependencies/libpqxx)
include_directories(dependencies/libpqxx/include)

target_include_directories(scholarly PUBLIC dependencies/imgui)
target_include_directories(scholarly PUBLIC dependencies/imgui/backends)

target_link_libraries(scholarly GL glfw pqxx pq)
