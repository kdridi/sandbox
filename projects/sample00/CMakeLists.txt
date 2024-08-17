project(sample00)

find_package(fmt CONFIG REQUIRED)

add_executable(sample00
    src/main.cpp
)

target_link_libraries(sample00 PRIVATE
    fmt::fmt
)
