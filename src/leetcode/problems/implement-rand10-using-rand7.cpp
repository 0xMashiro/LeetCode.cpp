#include "leetcode/problems/implement-rand10-using-rand7.h"

namespace leetcode {
namespace problem_470 {

// 默认的 rand7 实现（占位，实际由外部提供或测试注入）
static int defaultRand7() {
  // 默认实现，返回 1（实际运行时会由测试注入正确的 mock）
  return 1;
}

// 拒绝采样实现
// 时间复杂度：期望 O(1)，每次迭代有 40/49 的概率成功
// 空间复杂度：O(1)
static int rejectionSampling(Rand7Func& rand7) {
  while (true) {
    // 生成 0-48 的均匀分布（通过 (rand7()-1)*7 + (rand7()-1)）
    // 然后加 1 变成 1-49
    int num = (rand7() - 1) * 7 + rand7();  // 1-49
    // 如果 num <= 40，可以直接映射到 1-10
    if (num <= 40) {
      return (num - 1) % 10 + 1;
    }
    // 否则拒绝，重新采样
  }
}

// 优化版本：利用被拒绝的数减少调用次数
// 当 num 在 41-49 时（共 9 个数），可以再次利用
// 9 * 7 = 63 >= 60，还可以再生成一轮
static int optimizedRejection(Rand7Func& rand7) {
  while (true) {
    int a = rand7();
    int b = rand7();
    int num = (a - 1) * 7 + b;  // 1-49
    if (num <= 40) {
      return (num - 1) % 10 + 1;
    }
    // num 在 41-49，共 9 种可能
    // 再调用一次 rand7()，可以生成 9*7=63 种组合
    int c = rand7();
    num = (num - 41) * 7 + c;  // 0-62
    if (num < 60) {
      return num % 10 + 1;
    }
    // 否则继续循环，概率很低
  }
}

ImplementRand10UsingRand7Solution::ImplementRand10UsingRand7Solution()
    : rand7_(defaultRand7) {
  setMetaInfo({.id = 470,
               .title = "Implement Rand10() Using Rand7()",
               .url = "https://leetcode.com/problems/implement-rand10-using-rand7/"});
  
  // 注册策略：使用 lambda 捕获 this 来调用 rand7_
  registerStrategy("Rejection Sampling", [this]() {
    return rejectionSampling(rand7_);
  });
  registerStrategy("Optimized Rejection", [this]() {
    return optimizedRejection(rand7_);
  });
}

int ImplementRand10UsingRand7Solution::rand10() {
  return getSolution()();
}

}  // namespace problem_470
}  // namespace leetcode
