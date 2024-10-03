include(${CMAKE_CURRENT_SOURCE_DIR}/../common.cmake)

find_package(fmt CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics network CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    fmt::fmt
    sfml-system sfml-window sfml-graphics sfml-network
)
