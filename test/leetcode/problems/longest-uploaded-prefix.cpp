#include "leetcode/problems/longest-uploaded-prefix.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2424 {

// 示例 1
TEST(LongestUploadedPrefix, Example1) {
  LUPrefix server(4);
  server.upload(3);
  EXPECT_EQ(server.longest(), 0);
  server.upload(1);
  EXPECT_EQ(server.longest(), 1);
  server.upload(2);
  EXPECT_EQ(server.longest(), 3);
}

// 边界情况：只上传一个视频
TEST(LongestUploadedPrefix, SingleVideo) {
  LUPrefix server(1);
  EXPECT_EQ(server.longest(), 0);
  server.upload(1);
  EXPECT_EQ(server.longest(), 1);
}

// 边界情况：按顺序上传
TEST(LongestUploadedPrefix, SequentialUpload) {
  LUPrefix server(5);
  server.upload(1);
  EXPECT_EQ(server.longest(), 1);
  server.upload(2);
  EXPECT_EQ(server.longest(), 2);
  server.upload(3);
  EXPECT_EQ(server.longest(), 3);
  server.upload(4);
  EXPECT_EQ(server.longest(), 4);
  server.upload(5);
  EXPECT_EQ(server.longest(), 5);
}

// 边界情况：逆序上传
TEST(LongestUploadedPrefix, ReverseUpload) {
  LUPrefix server(5);
  server.upload(5);
  EXPECT_EQ(server.longest(), 0);
  server.upload(4);
  EXPECT_EQ(server.longest(), 0);
  server.upload(3);
  EXPECT_EQ(server.longest(), 0);
  server.upload(2);
  EXPECT_EQ(server.longest(), 0);
  server.upload(1);
  EXPECT_EQ(server.longest(), 5);
}

// 多次调用 longest
TEST(LongestUploadedPrefix, MultipleLongestCalls) {
  LUPrefix server(3);
  EXPECT_EQ(server.longest(), 0);
  server.upload(2);
  EXPECT_EQ(server.longest(), 0);
  EXPECT_EQ(server.longest(), 0);  // 再次调用
  server.upload(1);
  EXPECT_EQ(server.longest(), 2);
  EXPECT_EQ(server.longest(), 2);  // 再次调用
  server.upload(3);
  EXPECT_EQ(server.longest(), 3);
}

}  // namespace problem_2424
}  // namespace leetcode
