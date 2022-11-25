cmake_minimum_required(VERSION 3.16)
project(CLion_Snake)

set(CMAKE_CXX_STANDARD 14)

find_package(glfw3 3.3.8 REQUIRED HINTS "C:/Program Files (x86)/GLFW/lib/cmake/glfw3")
find_package(OpenGL REQUIRED)

add_executable(CLion_Snake main.cpp stb_image.cpp stb_image.h camera.h shader.h glad.c snake.h snack.h grid.h)

target_link_libraries(CLion_Snake "C:/Program Files (x86)/GLFW/lib/glfw3.lib")
target_link_libraries(CLion_Snake OpenGL::GL)
target_include_directories(CLion_Snake PUBLIC "C:/Program Files (x86)/GLFW/include/" C:/src/include)
#target_include_directories(CLion_Snake PUBLIC "C:/Program Files (x86)/GLFW/include/")
