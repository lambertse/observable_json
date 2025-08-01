project("observable_json_test")

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/../include"
)

add_executable(observable_json_test
    "main.cpp"
)
target_link_libraries(
  ${PROJECT_NAME} PUBLIC observable_json
)
