cmake_minimum_required(VERSION 3.16)

project(learnopengl
)

add_executable(${PROJECT_NAME} mesh.h model.h glad.c main.cpp shader.h camera.h stb_image.h stb_image.cpp)

target_link_libraries(${PROJECT_NAME} GL dl glfw assimp)


file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/modelShader.vs
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shaders)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/modelShader.fs
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shaders)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/models/backpack/backpack.obj
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/backpack)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Shader.vs
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Shader2.fs
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})