#include "leetcode/problems/debounce.h"

#include "gtest/gtest.h"

#include <chrono>

namespace leetcode {
namespace problem_2627 {

// 辅助结构体用于记录调用结果
struct CallResult {
  int time_ms;
  vector<int> inputs;
};

// 示例 1 测试
TEST(DebounceTest, Example1) {
  vector<CallResult> results;
  auto start = std::chrono::steady_clock::now();

  auto fn = [&results, &start](vector<int> inputs) {
    auto now = std::chrono::steady_clock::now();
    int elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - start)
            .count();
    results.push_back({elapsed, inputs});
  };

  Debounce debounced_fn(fn, 50);

  // 在 50ms 时调用，参数 [1]
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  debounced_fn({1});

  // 在 75ms 时调用，参数 [2]，这会取消第一次调用
  std::this_thread::sleep_for(std::chrono::milliseconds(25));
  debounced_fn({2});

  // 等待足够长时间让所有定时器完成
  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  // 验证结果：只有第二次调用被执行
  ASSERT_EQ(results.size(), 1);
  EXPECT_EQ(results[0].inputs, vector<int>({2}));
  // 执行时间应该在 125ms 左右（75ms + 50ms），允许一定误差
  EXPECT_GE(results[0].time_ms, 115);
  EXPECT_LE(results[0].time_ms, 145);
}

// 示例 2 测试：两次调用间隔足够长，都会执行
TEST(DebounceTest, Example2) {
  vector<CallResult> results;
  auto start = std::chrono::steady_clock::now();

  auto fn = [&results, &start](vector<int> inputs) {
    auto now = std::chrono::steady_clock::now();
    int elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - start)
            .count();
    results.push_back({elapsed, inputs});
  };

  Debounce debounced_fn(fn, 20);

  // 在 50ms 时调用，参数 [1]
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  debounced_fn({1});

  // 等待第一次调用执行完成（50ms + 20ms = 70ms）
  std::this_thread::sleep_for(std::chrono::milliseconds(50));

  // 在 100ms 时调用，参数 [2]
  std::this_thread::sleep_for(std::chrono::milliseconds(30));
  debounced_fn({2});

  // 等待第二次调用执行完成
  std::this_thread::sleep_for(std::chrono::milliseconds(50));

  // 验证结果：两次调用都被执行
  ASSERT_EQ(results.size(), 2);
  EXPECT_EQ(results[0].inputs, vector<int>({1}));
  EXPECT_EQ(results[1].inputs, vector<int>({2}));
  // 第一次执行时间应该在 70ms 左右，允许误差
  EXPECT_GE(results[0].time_ms, 60);
  EXPECT_LE(results[0].time_ms, 90);
  // 第二次执行时间应该在 120ms 左右，允许更大误差（累积延迟）
  EXPECT_GE(results[1].time_ms, 110);
  EXPECT_LE(results[1].time_ms, 170);
}

// 示例 3 测试：三次调用，第二次被取消
TEST(DebounceTest, Example3) {
  vector<CallResult> results;
  auto start = std::chrono::steady_clock::now();

  auto fn = [&results, &start](vector<int> inputs) {
    auto now = std::chrono::steady_clock::now();
    int elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - start)
            .count();
    results.push_back({elapsed, inputs});
  };

  Debounce debounced_fn(fn, 150);

  // 在 50ms 时调用，参数 [1, 2]
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  debounced_fn({1, 2});

  // 在 300ms 时调用，参数 [3, 4]
  std::this_thread::sleep_for(std::chrono::milliseconds(250));
  debounced_fn({3, 4});

  // 立即（300ms）再次调用，参数 [5, 6]，这会取消第二次调用
  debounced_fn({5, 6});

  // 等待所有定时器完成
  std::this_thread::sleep_for(std::chrono::milliseconds(200));

  // 验证结果：第一次和第三次调用被执行，第二次被取消
  ASSERT_EQ(results.size(), 2);
  EXPECT_EQ(results[0].inputs, (vector<int>{1, 2}));
  EXPECT_EQ(results[1].inputs, (vector<int>{5, 6}));
  // 第一次执行时间应该在 200ms 左右（50ms + 150ms）
  EXPECT_GE(results[0].time_ms, 185);
  EXPECT_LE(results[0].time_ms, 220);
  // 第三次执行时间应该在 450ms 左右（300ms + 150ms）
  EXPECT_GE(results[1].time_ms, 435);
  EXPECT_LE(results[1].time_ms, 470);
}

// 边界测试：t = 0，立即执行
TEST(DebounceTest, ZeroDelay) {
  vector<CallResult> results;
  auto start = std::chrono::steady_clock::now();

  auto fn = [&results, &start](vector<int> inputs) {
    auto now = std::chrono::steady_clock::now();
    int elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - start)
            .count();
    results.push_back({elapsed, inputs});
  };

  Debounce debounced_fn(fn, 0);

  debounced_fn({1});
  std::this_thread::sleep_for(std::chrono::milliseconds(20));
  debounced_fn({2});
  std::this_thread::sleep_for(std::chrono::milliseconds(20));

  // 两次调用都应该被执行，因为没有延迟
  ASSERT_EQ(results.size(), 2);
  EXPECT_EQ(results[0].inputs, vector<int>({1}));
  EXPECT_EQ(results[1].inputs, vector<int>({2}));
}

// 边界测试：单次调用
TEST(DebounceTest, SingleCall) {
  vector<CallResult> results;

  auto fn = [&results](vector<int> inputs) {
    results.push_back({0, inputs});
  };

  Debounce debounced_fn(fn, 50);

  debounced_fn({42});
  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  ASSERT_EQ(results.size(), 1);
  EXPECT_EQ(results[0].inputs, vector<int>({42}));
}

// 边界测试：连续快速调用，只有最后一次执行
TEST(DebounceTest, RapidCalls) {
  vector<CallResult> results;

  auto fn = [&results](vector<int> inputs) {
    results.push_back({0, inputs});
  };

  Debounce debounced_fn(fn, 100);

  // 快速连续调用 5 次
  for (int i = 1; i <= 5; ++i) {
    debounced_fn({i});
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(150));

  // 只有最后一次调用被执行
  ASSERT_EQ(results.size(), 1);
  EXPECT_EQ(results[0].inputs, vector<int>({5}));
}

}  // namespace problem_2627
}  // namespace leetcode
