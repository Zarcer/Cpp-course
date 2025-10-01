#include <spdlog/spdlog.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#include "../../libcompressor/include/libcompressor.hpp"

int main(int argc, char** argv) {
  spdlog::set_level(spdlog::level::err);

  if (argc < 3) {
    spdlog::error("Usage: compressor <zlib|bzip> <string>");
    return EXIT_FAILURE;
  }

  std::string alg = argv[1];
  const char* input_c = argv[2];
  libcompressor_Buffer in{const_cast<char*>(input_c), static_cast<int>(std::strlen(input_c))};

  libcompressor_CompressionAlgorithm a;
  if (alg == "zlib") {
    a = libcompressor_Zlib;
  } else if (alg == "bzip") {
    a = libcompressor_Bzip;
  } else {
    spdlog::error("Unknown algorithm: {}", alg);
    return EXIT_FAILURE;
  }

  libcompressor_Buffer out = libcompressor_compress(a, in);
  if (out.data == nullptr || out.size == 0) {
    spdlog::error("Compression failed");
    return EXIT_FAILURE;
  }

  for (int i = 0; i < out.size; ++i) {
    std::printf("%02hhx", static_cast<unsigned char>(out.data[i]));
  }
  std::printf("\n");

  std::free(out.data);
  return EXIT_SUCCESS;
}
