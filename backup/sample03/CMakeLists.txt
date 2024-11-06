include(${CMAKE_CURRENT_SOURCE_DIR}/../common.cmake)

target_link_libraries(${PROJECT_NAME} PUBLIC
    {NAMESPACE}_module)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE
²   fmt::fmt)

find_package(PhysFS CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE
    $<IF:$<TARGET_EXISTS:PhysFS::PhysFS>,PhysFS::PhysFS,PhysFS::PhysFS-static>)
