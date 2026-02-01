#include "leetcode/problems/minimum-addition-to-make-integer-beautiful.h"

namespace leetcode {
namespace problem_2457 {

// 辅助函数：计算数字的各位之和
static long long digitSum(long long n) {
  long long sum = 0;
  while (n > 0) {
    sum += n % 10;
    n /= 10;
  }
  return sum;
}

// 贪心策略：从低位到高位逐步进位，使数字之和减小
// 时间复杂度: O(log n), 空间复杂度: O(1)
static long long solution1(long long n, int target) {
  // 如果当前已经是美丽数，直接返回 0
  if (digitSum(n) <= target) {
    return 0;
  }
  
  long long original = n;
  long long round = 10;  // 当前要进位的基数（10, 100, 1000...）
  
  // 从低位到高位逐步尝试进位
  while (true) {
    // 将 n 向上取整到 round 的倍数
    long long next = ((n / round) + 1) * round;
    long long addition = next - original;  // 需要增加的数值
    
    // 检查进位后的数字之和是否满足条件
    if (digitSum(next) <= target) {
      return addition;
    }
    
    // 继续向更高位进位
    round *= 10;
  }
  
  return 0;  // 理论上不会到达这里，因为题目保证有解
}

// 优化版本：避免重复计算，直接模拟进位过程
// 时间复杂度: O(log n), 空间复杂度: O(1)
static long long solution2(long long n, int target) {
  if (digitSum(n) <= target) {
    return 0;
  }
  
  long long original = n;
  long long power = 1;  // 10^i
  
  while (digitSum(n) > target) {
    // 将当前位及更低位置零，并向高位进 1
    n = (n / (power * 10) + 1) * (power * 10);
    power *= 10;
  }
  
  return n - original;
}

MinimumAdditionToMakeIntegerBeautifulSolution::MinimumAdditionToMakeIntegerBeautifulSolution() {
  setMetaInfo({.id = 2457,
               .title = "Minimum Addition to Make Integer Beautiful",
               .url = "https://leetcode.com/problems/minimum-addition-to-make-integer-beautiful/"});
  registerStrategy("Greedy - Round Up", solution1);
  registerStrategy("Greedy - Direct Simulation", solution2);
}

long long MinimumAdditionToMakeIntegerBeautifulSolution::makeIntegerBeautiful(long long n, int target) {
  return getSolution()(n, target);
}

}  // namespace problem_2457
}  // namespace leetcode
