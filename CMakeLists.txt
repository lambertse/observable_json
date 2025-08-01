cmake_minimum_required(VERSION 3.16)
project(observable_json)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Fetch json11
include(FetchContent)
FetchContent_Declare(
    json11
    GIT_REPOSITORY https://github.com/dropbox/json11.git
    GIT_TAG master
)
FetchContent_MakeAvailable(json11)

# Gather headers and sources
file(GLOB HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/observable_json/*.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/json_base/*.hpp")
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/json_base/*.cpp")

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PUBLIC json11)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
