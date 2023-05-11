cmake_minimum_required(VERSION 3.25)
project(hello_opengl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -I/opt/homebrew/include)
include_directories(./include/)
link_directories(/opt/homebrew/lib)


add_executable(hello_opengl main.cpp include/glad.c)
target_link_libraries(hello_opengl glfw.3)
