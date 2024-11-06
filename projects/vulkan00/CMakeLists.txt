include(${CMAKE_CURRENT_SOURCE_DIR}/../common.cmake)

find_package(Vulkan REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Vulkan::Vulkan
)
