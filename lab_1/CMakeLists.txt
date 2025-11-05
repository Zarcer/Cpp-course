cmake_minimum_required(VERSION 3.24)
project(compressor_project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

include(GNUInstallDirs)
enable_testing()

add_subdirectory(libcompressor)
add_subdirectory(compressor)]
add_subdirectory(libcompressor/tests)

file(GLOB_RECURSE ALL_SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/libcompressor/src/*.cpp
        ${CMAKE_SOURCE_DIR}/libcompressor/include/*.hpp
        ${CMAKE_SOURCE_DIR}/compressor/src/*.cpp
        ${CMAKE_SOURCE_DIR}/libcompressor/tests/*.cpp
)
find_program(CLANG_FORMAT_EXE NAMES clang-format)
if(CLANG_FORMAT_EXE)
    add_custom_target(format
            COMMAND ${CLANG_FORMAT_EXE} -i ${ALL_SOURCE_FILES}
            COMMENT "Run clang-format on sources")
endif()

find_program(CLANG_TIDY_EXE NAMES clang-tidy)
if(CLANG_TIDY_EXE)
    add_custom_target(tidy
            COMMAND ${CLANG_TIDY_EXE} -p ${CMAKE_BINARioY_DIR} ${ALL_SOURCE_FILES}
            COMMENT "Run clang-tidy on sources")
endif()
