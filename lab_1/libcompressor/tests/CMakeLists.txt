find_package(GTest REQUIRED)

add_executable(libcompressortest
        libcompressortest.cpp
)

target_link_libraries(libcompressortest PRIVATE libcompressor GTest::gtest_main)
target_compile_features(libcompressortest PRIVATE cxx_std_20)

if(MSVC)
    target_compile_options(libcompressortest PRIVATE /W4 /WX)
else()
    target_compile_options(libcompressortest PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

add_test(NAME libcompressor_tests COMMAND libcompressortest)
set_tests_properties(libcompressor_tests PROPERTIES
        ENVIRONMENT "GTEST_OUTPUT=xml:${CMAKE_BINARY_DIR}/test_results.xml")
