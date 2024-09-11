include(${CMAKE_CURRENT_SOURCE_DIR}/../common.cmake)

find_package(fmt CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    GL_SILENCE_DEPRECATION
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    fmt::fmt
    OpenGL::GL
    glfw
)
