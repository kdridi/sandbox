include(${CMAKE_CURRENT_SOURCE_DIR}/../common.cmake)

find_package(fmt CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics network CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    fmt::fmt
    imgui::imgui
    ImGui-SFML::ImGui-SFML
    sfml-system
    sfml-window
    sfml-graphics
    sfml-network)
