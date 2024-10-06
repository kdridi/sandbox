include(${CMAKE_CURRENT_SOURCE_DIR}/../common.cmake)

find_package(GLEW REQUIRED)
find_package(SFML COMPONENTS system window graphics network CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    GLEW::GLEW
    sfml-system sfml-window sfml-graphics sfml-network
    ${NAMESPACE}_pathSolver
)
