include(${CMAKE_CURRENT_SOURCE_DIR}/../common.cmake)

target_link_libraries(${PROJECT_NAME} PUBLIC ${NAMESPACE}_module)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt)
