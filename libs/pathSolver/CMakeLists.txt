project(ArykowPathSolver)

find_package(spdlog CONFIG REQUIRED)

add_library(ArykowPathSolver STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/arykow/PathSolver.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PathSolver.cpp
)

target_include_directories(ArykowPathSolver PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(ArykowPathSolver PRIVATE
    spdlog::spdlog
)
