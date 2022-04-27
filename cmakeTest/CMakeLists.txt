cmake_minimum_required(VERSION 3.0.0)
project(Models VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Models main.cpp mesh.h model.h glad.c shader.h camera.h stb_image.h stb_image.cpp)
target_link_libraries(${PROJECT_NAME} GL dl glfw assimp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/models/backpack.obj
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/backpack)