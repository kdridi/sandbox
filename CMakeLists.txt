cmake_minimum_required(VERSION 3.22)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

get_filename_component(NAMESPACE ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${NAMESPACE})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DNAMESPACE="${NAMESPACE}")

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/W4 /WX)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

file(GLOB LIB_SUBDIRS "libs/*")

foreach(subdir ${LIB_SUBDIRS})
  if(IS_DIRECTORY ${subdir})
    add_subdirectory(${subdir})
  endif()
endforeach()

file(GLOB APP_SUBDIRS "projects/*")

foreach(subdir ${APP_SUBDIRS})
  if(IS_DIRECTORY ${subdir})
    add_subdirectory(${subdir})
  endif()
endforeach()
