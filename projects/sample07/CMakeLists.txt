include(${CMAKE_CURRENT_SOURCE_DIR}/../common.cmake)

find_package(fmt CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics network CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(freeimage CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    fmt::fmt
    sfml-system sfml-window sfml-graphics sfml-network
    spdlog::spdlog
    freeimage::FreeImage freeimage::FreeImagePlus
    ${NAMESPACE}_pathSolver
    ${NAMESPACE}_envVars
)
