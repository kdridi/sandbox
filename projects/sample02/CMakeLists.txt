project(sample02)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

add_executable(sample02
    src/main.cpp
)

target_compile_definitions(sample02 PRIVATE
    GL_SILENCE_DEPRECATION
)

target_link_libraries(sample02 PRIVATE
    sfml-system sfml-network sfml-graphics sfml-window
)
