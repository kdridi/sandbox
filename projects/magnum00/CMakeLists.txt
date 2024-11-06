include(${CMAKE_CURRENT_SOURCE_DIR}/../common.cmake)

find_package(Corrade REQUIRED Main)
target_link_libraries(${PROJECT_NAME} PRIVATE Corrade::Main)
set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

find_package(Magnum REQUIRED GL Shaders Sdl2Application)
target_link_libraries(${PROJECT_NAME} PRIVATE Magnum::Application Magnum::GL Magnum::Magnum Magnum::Shaders)