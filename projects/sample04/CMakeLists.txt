include(${CMAKE_CURRENT_SOURCE_DIR}/../common.cmake)

find_package(fmt CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    fmt::fmt
)
