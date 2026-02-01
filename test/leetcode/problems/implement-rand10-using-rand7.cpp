#include "leetcode/problems/implement-rand10-using-rand7.h"

#include "gtest/gtest.h"

#include <random>

namespace leetcode {
namespace problem_470 {

// 模拟 rand7() 的随机数生成器
class MockRand7 {
 public:
  MockRand7() : gen_(std::random_device{}()), dist_(1, 7) {}

  int operator()() { return dist_(gen_); }

 private:
  std::mt19937 gen_;
  std::uniform_int_distribution<> dist_;
};

class ImplementRand10UsingRand7Test : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override {
    solution_.setStrategy(GetParam());
    // 注入 mock rand7 函数
    solution_.setRand7([this]() { return mock_rand7_(); });
  }

  ImplementRand10UsingRand7Solution solution_;
  MockRand7 mock_rand7_;
};

TEST_P(ImplementRand10UsingRand7Test, ReturnsValidRange) {
  // 测试多次调用，确保返回值都在 [1, 10] 范围内
  for (int i = 0; i < 1000; ++i) {
    int result = solution_.rand10();
    EXPECT_GE(result, 1);
    EXPECT_LE(result, 10);
  }
}

TEST_P(ImplementRand10UsingRand7Test, DistributionTest) {
  // 统计测试：确保每个数字都会出现（概率性测试）
  std::vector<int> count(11, 0);  // 索引 1-10
  const int iterations = 10000;
  
  for (int i = 0; i < iterations; ++i) {
    int result = solution_.rand10();
    count[result]++;
  }
  
  // 每个数字的期望出现次数约为 iterations/10 = 1000
  // 检查每个数字至少出现一次（概率极高）
  for (int i = 1; i <= 10; ++i) {
    EXPECT_GT(count[i], 0) << "Number " << i << " was never generated";
  }
  
  // 检查分布大致均匀（允许 ±30% 的误差）
  double expected = iterations / 10.0;
  for (int i = 1; i <= 10; ++i) {
    EXPECT_NEAR(count[i], expected, expected * 0.3)
        << "Number " << i << " has uneven distribution";
  }
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode,
    ImplementRand10UsingRand7Test,
    ::testing::ValuesIn(ImplementRand10UsingRand7Solution().getStrategyNames()));

}  // namespace problem_470
}  // namespace leetcode
