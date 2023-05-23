cmake_minimum_required(VERSION 3.25)
project(hello_opengl)

set(CMAKE_CXX_STANDARD 17)

# Check the system processor architecture
if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm64")
    message("Building on macOS ARM")
    # Set the include and library directories for GLFW for ARM
    set(GLFW_INCLUDE_DIR /opt/homebrew/include)
    set(GLFW_LIBRARY_DIR /opt/homebrew/lib)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
    message("Building on macOS Intel")
    # Set the include and library directories for GLFW for Intel
    set(GLFW_INCLUDE_DIR /usr/local/include)
    set(GLFW_LIBRARY_DIR /usr/local/lib)
endif()

#set(CMAKE_CXX_FLAGS -I/opt/homebrew/include)
#include_directories(./include/)
#link_directories(/opt/homebrew/lib)
message("GLFW_INCLUDE_DIR: ${GLFW_INCLUDE_DIR}")
set(CMAKE_CXX_FLAGS -I${GLFW_INCLUDE_DIR})
include_directories(./include/)
link_directories(${GLFW_LIBRARY_DIR})

add_executable(hello_opengl hello_triangle_indexed.cpp include/glad.c)
target_link_libraries(hello_opengl glfw.3)

add_executable(E5_Transformations shader/transformations.cpp include/glad.c shader/stb_image.cpp)
target_link_libraries(E5_Transformations glfw.3)

add_executable(E5_MyTransformations shader/mytransformations.cpp include/glad.c shader/stb_image.cpp)
target_link_libraries(E5_MyTransformations glfw.3)
