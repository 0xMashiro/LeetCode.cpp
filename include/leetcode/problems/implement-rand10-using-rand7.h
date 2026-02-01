#include "leetcode/core.h"

namespace leetcode {
namespace problem_470 {

// 函数类型定义：rand7 函数指针类型
using Rand7Func = std::function<int()>;

using Func = std::function<int()>;

/**
 * 470. Implement Rand10() Using Rand7()
 * https://leetcode.com/problems/implement-rand10-using-rand7/
 *
 * 思路：拒绝采样（Rejection Sampling）
 * - 调用两次 rand7() 可以生成 1-49 的均匀分布
 * - 取 1-40 范围内的数，对 10 取模加 1 得到 1-10
 * - 41-49 范围内的数被拒绝，重新采样
 * - 期望调用次数：2 * (49/40) = 2.45 次
 */
class ImplementRand10UsingRand7Solution : public SolutionBase<Func> {
 public:
  int rand10();

  // 设置 rand7 函数（用于测试注入 mock）
  void setRand7(Rand7Func rand7_func) { rand7_ = rand7_func; }

  ImplementRand10UsingRand7Solution();

 private:
  Rand7Func rand7_;
};

}  // namespace problem_470
}  // namespace leetcode
