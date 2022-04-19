cmake_minimum_required(VERSION 3.16)

project(learnopengl
)

add_executable(${PROJECT_NAME} glad.c main.cpp shader.h camera.h stb_image.h stb_image.cpp)

target_link_libraries(${PROJECT_NAME} GL dl glfw)


file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Shader.vs
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Shader1.fs
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
     file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Shader2.fs
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
     file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/ambientShader.fs
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
     file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/diffuseShader.vs
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
     file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/diffuseShader.fs
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})