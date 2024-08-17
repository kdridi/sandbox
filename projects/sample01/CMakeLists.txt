project(sample01)

find_package(fmt CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(sample01
    src/main.cpp
)

target_compile_definitions(sample01 PRIVATE
    GL_SILENCE_DEPRECATION
)

target_link_libraries(sample01 PRIVATE
    OpenGL::GL
    fmt::fmt
    glfw
)
