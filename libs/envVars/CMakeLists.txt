include(${CMAKE_CURRENT_SOURCE_DIR}/../common.cmake)

find_package(spdlog CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    spdlog::spdlog
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${NAMESPACE}_module
)
