include(${CMAKE_CURRENT_SOURCE_DIR}/../common.cmake)

target_link_libraries(${PROJECT_NAME} PRIVATE ${NAMESPACE}_pathSolver)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
