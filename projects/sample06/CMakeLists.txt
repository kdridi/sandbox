include(${CMAKE_CURRENT_SOURCE_DIR}/../common.cmake)

find_package(spdlog CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics network CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-system sfml-window sfml-graphics sfml-network
    spdlog::spdlog
    ${NAMESPACE}_pathSolver
)
