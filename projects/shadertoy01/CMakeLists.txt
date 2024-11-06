include(${CMAKE_CURRENT_SOURCE_DIR}/../common.cmake)

target_link_libraries(${PROJECT_NAME} PRIVATE ${NAMESPACE}_pathSolver)

find_package(GLEW REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)

find_package(SFML COMPONENTS system window graphics network CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-window sfml-graphics sfml-network)
