project(sample04)

find_package(fmt CONFIG REQUIRED)

add_executable(sample04
    src/main.cpp
)

target_link_libraries(sample04 PRIVATE
    fmt::fmt
)

add_custom_command(TARGET sample04 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:sample04>/assets
)
