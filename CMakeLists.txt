cmake_minimum_required(VERSION 3.16)

project(learnopengl
)

add_executable(${PROJECT_NAME} glad.c main.cpp)

target_link_libraries(${PROJECT_NAME} GL dl glfw)


