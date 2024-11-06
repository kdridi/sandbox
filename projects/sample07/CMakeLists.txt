include(${CMAKE_CURRENT_SOURCE_DIR}/../common.cmake)

target_link_libraries(${PROJECT_NAME} PRIVATE ${NAMESPACE}_pathSolver)
target_link_libraries(${PROJECT_NAME} PRIVATE ${NAMESPACE}_envVars)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)

find_package(SFML COMPONENTS system window graphics network CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-window sfml-graphics sfml-network)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)

find_package(freeimage CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE freeimage::FreeImage freeimage::FreeImagePlus)
