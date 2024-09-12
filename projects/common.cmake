get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJECT_NAME})

file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/assets)
    set(OUTPUT_DIR $<TARGET_FILE_DIR:${PROJECT_NAME}>)

    if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
        add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND zip -r ${CMAKE_CURRENT_BINARY_DIR}/assets.zip assets
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Génération du fichier ${CMAKE_CURRENT_BINARY_DIR}/assets.zip"
        )
    else()
        add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND tar -cf ${CMAKE_CURRENT_BINARY_DIR}/assets.zip --format=zip -C ${CMAKE_CURRENT_SOURCE_DIR} assets
            DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/assets
            COMMENT "Génération du fichier ${CMAKE_CURRENT_BINARY_DIR}/assets.zip"
        )
    endif()
    
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${OUTPUT_DIR}/assets
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/assets
        COMMENT "Génération du repertoire ${OUTPUT_DIR}/assets"
    )
endif()
