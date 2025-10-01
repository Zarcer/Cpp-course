add_library(libcompressor STATIC
        src/libcompressor.cpp
)

target_include_directories(libcompressor PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(libcompressor PUBLIC cxx_std_20)

if(MSVC)
    target_compile_options(libcompressor PRIVATE /W4 /WX)
else()
    target_compile_options(libcompressor PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

find_package(ZLIB REQUIRED)
find_package(BZip2 REQUIRED)

target_link_libraries(libcompressor PRIVATE ZLIB::ZLIB BZip2::BZip2)

# Doxygen (если установлен)
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_BINARY_DIR}/Doxyfile)
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    add_custom_target(doc
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen")
endif()

# Установка
install(TARGETS libcompressor
        EXPORT libcompressorTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT libcompressorTargets
        FILE libcompressorTargets.cmake
        NAMESPACE libcompressor::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libcompressor
)
