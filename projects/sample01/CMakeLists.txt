include(${CMAKE_CURRENT_SOURCE_DIR}/../common.cmake)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE
    fmt::fmt)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME}
    PRIVATE OpenGL::GL)
target_compile_definitions(${PROJECT_NAME} PRIVATE GL_SILENCE_DEPRECATION)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw)
