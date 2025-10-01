#include "../include/libcompressor.hpp"

#include <bzlib.h>
#include <zlib.h>

#include <cstdlib>
#include <cstring>

libcompressor_Buffer libcompressor_compress(libcompressor_CompressionAlgorithm algo, libcompressor_Buffer input) {
  if (input.data == nullptr || input.size <= 0) {
    return {nullptr, 0};
  }

  unsigned long in_size = static_cast<unsigned long>(input.size);
  unsigned long out_capacity = in_size + 1024;
  char* out = static_cast<char*>(std::malloc(out_capacity));
  if (!out) return {nullptr, 0};

  if (algo == libcompressor_Zlib) {
    uLongf destLen = static_cast<uLongf>(out_capacity);
    int res = compress2(reinterpret_cast<Bytef*>(out), &destLen, reinterpret_cast<const Bytef*>(input.data), in_size,
                        Z_DEFAULT_COMPRESSION);
    if (res != Z_OK) {
      std::free(out);
      return {nullptr, 0};
    }
    return {out, static_cast<int>(destLen)};
  } else if (algo == libcompressor_Bzip) {
    unsigned int destLen = static_cast<unsigned int>(out_capacity);
    int res = BZ2_bzBuffToBuffCompress(out, &destLen, input.data, static_cast<unsigned int>(in_size), 1 /*blocksize*/,
                                       0 /*verbosity*/, 0 /*workfactor*/);
    if (res != BZ_OK) {
      std::free(out);
      return {nullptr, 0};
    }
    return {out, static_cast<int>(destLen)};
  }

  std::free(out);
  return {nullptr, 0};
}
