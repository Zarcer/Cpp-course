#include <gtest/gtest.h>

#include <cstring>

#include "../include/libcompressor.hpp"

TEST(CompressorZlib, EmptyInputProducesEmptyOutput) {
  libcompressor_Buffer in{nullptr, 0};
  auto out = libcompressor_compress(libcompressor_Zlib, in);
  EXPECT_EQ(out.data, nullptr);
  EXPECT_EQ(out.size, 0);
}

TEST(CompressorBzip, NonEmptyInputProducesNonEmptyOutput) {
  const char* s = "abc";
  libcompressor_Buffer in{const_cast<char*>(s), 3};
  auto out = libcompressor_compress(libcompressor_Bzip, in);
  EXPECT_NE(out.data, nullptr);
  EXPECT_GT(out.size, 0);
  std::free(out.data);
}

TEST(CompressorBzip, EmptyInputProducesEmptyOutput) {
  libcompressor_Buffer in{nullptr, 0};
  auto out = libcompressor_compress(libcompressor_Bzip, in);
  EXPECT_EQ(out.data, nullptr);
  EXPECT_EQ(out.size, 0);
}

TEST(CompressorZlib, ExpectedBytesForTestString) {
  const char* s = "test_string";
  libcompressor_Buffer in{const_cast<char*>(s), 11};
  auto out = libcompressor_compress(libcompressor_Zlib, in);

  unsigned char expected[] = {0x78, 0x9c, 0x2b, 0x49, 0x2d, 0x2e, 0x89, 0x2f, 0x2e, 0x29,
                              0xca, 0xcc, 0x4b, 0x07, 0x00, 0x1c, 0x79, 0x04, 0xb7};
  ASSERT_EQ(out.size, sizeof(expected));
  EXPECT_EQ(std::memcmp(out.data, expected, sizeof(expected)), 0);

  std::free(out.data);
}

TEST(CompressorBzip, ExpectedBytesForTestString) {
  const char* s = "test_string";
  libcompressor_Buffer in{const_cast<char*>(s), 11};
  auto out = libcompressor_compress(libcompressor_Bzip, in);

  unsigned char expected[] = {0x42, 0x5a, 0x68, 0x31, 0x31, 0x41, 0x59, 0x26, 0x53, 0x59, 0x4a, 0x7c,
                              0x69, 0x05, 0x00, 0x00, 0x04, 0x83, 0x80, 0x00, 0x00, 0x82, 0xa1, 0x1c,
                              0x00, 0x20, 0x00, 0x22, 0x03, 0x68, 0x84, 0x30, 0x22, 0x50, 0xdf, 0x04,
                              0x99, 0xe2, 0xee, 0x48, 0xa7, 0x0a, 0x12, 0x09, 0x4f, 0x8d, 0x20, 0xa0};
  ASSERT_EQ(out.size, sizeof(expected));
  EXPECT_EQ(std::memcmp(out.data, expected, sizeof(expected)), 0);

  std::free(out.data);
}
