#ifndef LIBCOMPRESSOR_HPP
#define LIBCOMPRESSOR_HPP

#include <cstdlib>

/**
 * @file libcompressor.hpp
 * @brief Minimal C++ wrapper interface for compression using zlib and bzip2
 */

/**
 * @brief Supported compression algorithms
 */
enum libcompressor_CompressionAlgorithm {
  libcompressor_Zlib, /**< zlib */
  libcompressor_Bzip  /**< bzip2 */
};

/**
 * @brief Buffer that holds pointer to malloc-allocated data and its size
 */
struct libcompressor_Buffer {
  char* data; /**< Pointer to malloc-allocated buffer */
  int size;   /**< Size of the buffer in bytes */
};

/**
 * @brief Compress an input buffer using the chosen algorithm.
 *
 * Allocates memory for result with std::malloc().
 * Initial output buffer size = input.size + 1024.
 *
 * @param algo Algorithm to use
 * @param input Input buffer
 * @return Output buffer (valid on success, {nullptr,0} on error).
 */
libcompressor_Buffer libcompressor_compress(libcompressor_CompressionAlgorithm algo, libcompressor_Buffer input);

#endif  // LIBCOMPRESSOR_HPP
