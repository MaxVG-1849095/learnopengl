cmake_minimum_required(VERSION 3.16)

project(learnopengl
)

add_executable(${PROJECT_NAME} glad.c main.cpp shader.h camera.h stb_image.h stb_image.cpp)

target_link_libraries(${PROJECT_NAME} GL dl glfw)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/3.3.Shader.vs
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/3.3.Shader.fs
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
     file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/container.jpg
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
     file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/awesomeface.png
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})