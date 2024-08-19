project(sample06)

find_package(spdlog CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

add_executable(sample06
    src/main.cpp

    src/Level.h
    src/ParticleSystem.h
    src/ParticleSystem.cpp
    src/TileMap.h
    src/TileMap.cpp
)

target_compile_definitions(sample02 PRIVATE
    GL_SILENCE_DEPRECATION
)

target_link_libraries(sample06 PRIVATE
    sfml-system sfml-network sfml-graphics sfml-window
    spdlog::spdlog
    ArykowPathSolver
)

add_custom_command(TARGET sample06 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:sample06>/assets
)
