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

add_executable(hello_triangulo hello_triangle.cpp include/glad.c)
target_link_libraries(hello_triangulo glfw.3)

add_executable(hello_piramide hello_piramide.cpp include/glad.c)
target_link_libraries(hello_piramide glfw.3)

add_executable(hello_trian_indexed hello_triangle_indexed.cpp include/glad.c)
target_link_libraries(hello_trian_indexed glfw.3)

add_executable(hello_exe1 hello_exercises/two_tri.cpp include/glad.c)
target_link_libraries(hello_exe1 glfw.3)

add_executable(hello_exe1_sol hello_exercises/two_tri_sol.cpp include/glad.c)
target_link_libraries(hello_exe1_sol glfw.3)

add_executable(hello_exe2 hello_exercises/exe2_two_tri_diff.cpp include/glad.c)
target_link_libraries(hello_exe2 glfw.3)

add_executable(hello_exe3 hello_exercises/exe3_two_shaders.cpp include/glad.c)
target_link_libraries(hello_exe3 glfw.3)

add_executable(E1_Shaders_Uniform shadersLearning/uniform/shaders_uniform.cpp include/glad.c)
target_link_libraries(E1_Shaders_Uniform glfw.3)

add_executable(E1_Shaders_Interpolation shadersLearning/interpolation/shaders_interpolation.cpp include/glad.c)
target_link_libraries(E1_Shaders_Interpolation glfw.3)

add_executable(E1_Shaders_Class shadersLearning/shader_class/shaders_class.cpp include/glad.c)
target_link_libraries(E1_Shaders_Class glfw.3)

add_executable(E1_Shaders_ex1 shadersLearning/shader_ex1.cpp include/glad.c)
target_link_libraries(E1_Shaders_ex1 glfw.3)

add_executable(E1_Shaders_ex2 shadersLearning/shader_ex2.cpp include/glad.c)
target_link_libraries(E1_Shaders_ex2 glfw.3)

add_executable(E1_Shaders_ex3 shadersLearning/shader_ex3.cpp include/glad.c)
target_link_libraries(E1_Shaders_ex3 glfw.3)

add_executable(E5_Transformations shader/transformations.cpp include/glad.c shader/stb_image.cpp)
target_link_libraries(E5_Transformations glfw.3)

add_executable(E5_MyTransformations shader/mytransformations.cpp include/glad.c shader/stb_image.cpp)
target_link_libraries(E5_MyTransformations glfw.3)

add_executable(E2_Iluminacion shader/basic_lighting_diffuse.cpp include/glad.c shader/stb_image.cpp)
target_link_libraries(E2_Iluminacion glfw.3)

add_executable(T9_Npiramides shader/mynpiramidesilum.cpp include/glad.c shader/stb_image.cpp)
target_link_libraries(T9_Npiramides glfw.3)

add_executable(Conejo shader/main.cpp include/glad.c shader/glut_ply.cpp shader/Objeto.cpp shader/BoundingVolume.h)
target_link_libraries(Conejo glfw.3)