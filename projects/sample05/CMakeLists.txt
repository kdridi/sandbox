project(sample05)

find_package(spdlog CONFIG REQUIRED)

add_executable(sample05
    src/main.cpp
)

target_link_libraries(sample05 PRIVATE
    spdlog::spdlog
    ArykowPathSolver
)

add_custom_command(TARGET sample05 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:sample05>/assets
)
