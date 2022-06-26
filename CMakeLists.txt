cmake_minimum_required(VERSION 3.10)

project(engine C)

add_executable(engine main.c)

find_package(glfw3 3.3 REQUIRED)

target_link_libraries(engine glfw)

find_package(OpenGL REQUIRED)

target_link_libraries(engine OpenGL::GL)

