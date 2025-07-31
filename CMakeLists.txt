cmake_minimum_required(VERSION 3.16)
project(observable_json)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Gather all source files in source folder
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Gather all header files in include folder (not strictly necessary for build, but for IDEs)
file(GLOB HEADERS "${CMAKE_SOURCE_DIR}/include/*.h" "${CMAKE_SOURCE_DIR}/include/*.hpp")

if(BUILD_SHARED_LIBS)
    set(PROJECT_NAME "${PROJECT_NAME}_shared")
else()
    set(PROJECT_NAME "${PROJECT_NAME}_static")
endif()

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
