include(${CMAKE_CURRENT_SOURCE_DIR}/../common.cmake)

find_package(Vulkan REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Vulkan::Vulkan
    glfw
)
