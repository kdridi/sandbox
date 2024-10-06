include(${CMAKE_CURRENT_SOURCE_DIR}/../common.cmake)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(OpenCL CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-system
    sfml-network
    sfml-graphics
    sfml-window

    OpenCL::Headers
    OpenCL::HeadersCpp
    OpenCL::Utils
    OpenCL::UtilsCpp
)
