project(sample03)

find_package(fmt CONFIG REQUIRED)
find_package(PhysFS CONFIG REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

add_custom_command(
    OUTPUT ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets.zip
    COMMAND tar -cf ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets.zip --format=zip -C ${CMAKE_CURRENT_SOURCE_DIR} assets
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/assets
    COMMENT "Génération du fichier assets.zip"
)

add_custom_target(zip_assets ALL
    DEPENDS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets.zip
)

add_executable(sample03
    src/arykow/assets/Loader.h
    src/arykow/assets/Loader.cpp
    src/main.cpp
)

target_link_libraries(sample03 PRIVATE
    fmt::fmt
    $<IF:$<TARGET_EXISTS:PhysFS::PhysFS>,PhysFS::PhysFS,PhysFS::PhysFS-static>
)

add_dependencies(sample03 zip_assets)

add_custom_command(TARGET sample03 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets.zip
    $<TARGET_FILE_DIR:sample03>
)
