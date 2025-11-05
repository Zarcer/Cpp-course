cmake_minimum_required(VERSION 3.10)
project(SimpleRegex LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

add_library(regexlib src/regex.cpp)
add_executable(regex_main src/main.cpp)
target_link_libraries(regex_main PRIVATE regexlib)

add_executable(regex_tests tests/tests.cpp)
target_link_libraries(regex_tests PRIVATE regexlib)

enable_testing()
add_test(NAME regex_tests COMMAND regex_tests)