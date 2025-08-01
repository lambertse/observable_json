cmake_minimum_required(VERSION 3.16)
project(observable_json)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(ENABLE_TESTING OFF)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Gather all header files in include folder (not strictly necessary for build, but for IDEs)
file(GLOB HEADERS "${CMAKE_SOURCE_DIR}/include/observable_json/*.h")

message(STATUS "Headers found: ${HEADERS}")

if(BUILD_SHARED_LIBS)
    set(PROJECT_NAME "${PROJECT_NAME}")
else()
    set(PROJECT_NAME "${PROJECT_NAME}")
endif()

add_library(${PROJECT_NAME} INTERFACE ${HEADERS})

if(ENABLE_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
