#include "leetcode/problems/find-maximum-balanced-xor-subarray-length.h"

namespace leetcode {
namespace problem_3755 {

// 前缀异或 + 前缀奇偶统计
// 对于子数组 [i, j]（包含），需要满足：
// 1. XOR[i..j] = 0  => prefixXOR[j+1] == prefixXOR[i]
// 2. even[i..j] == odd[i..j]  => (evenPrefix[j+1] - oddPrefix[j+1]) == (evenPrefix[i] - oddPrefix[i])
// 综合：寻找满足 (xorValue, diff) 相同的两个位置，计算最大距离
// 时间复杂度: O(n), 空间复杂度: O(n)
static int solution1(vector<int>& nums) {
  const int n = nums.size();
  
  // key: {xorValue, diff}, value: 第一次出现的位置
  unordered_map<long long, int> firstPos;
  
  long long xorPrefix = 0;
  int evenCount = 0;
  int oddCount = 0;
  
  // 初始状态：位置0（在数组前面）
  // 使用配对编码：xorPrefix * 200001 + diff，或者使用pair作为key
  auto encode = [](long long x, long long d) -> long long {
    // 将 diff 映射到非负数（diff 范围是 [-n, n]）
    // 使用 200001 作为偏移量（最大 n = 100000）
    return x * 200001LL + (d + 100000LL);
  };
  
  firstPos[encode(0, 0)] = 0;
  
  int maxLen = 0;
  
  for (int i = 0; i < n; ++i) {
    xorPrefix ^= nums[i];
    if (nums[i] % 2 == 0) {
      evenCount++;
    } else {
      oddCount++;
    }
    
    int diff = evenCount - oddCount;
    long long key = encode(xorPrefix, diff);
    
    if (firstPos.find(key) != firstPos.end()) {
      // 找到了一个满足条件的子数组
      int len = i + 1 - firstPos[key];
      maxLen = max(maxLen, len);
    } else {
      // 只记录第一次出现的位置
      firstPos[key] = i + 1;
    }
  }
  
  return maxLen;
}

// 优化版本：使用 pair 作为哈希表键，更清晰
static int solution2(vector<int>& nums) {
  const int n = nums.size();
  
  // 使用 pair 作为 key 的哈希表
  struct PairHash {
    size_t operator()(const pair<int, int>& p) const {
      return hash<long long>()((static_cast<long long>(p.first) << 32) | static_cast<unsigned>(p.second));
    }
  };
  
  unordered_map<pair<int, int>, int, PairHash> firstPos;
  
  int xorPrefix = 0;
  int evenCount = 0;
  int oddCount = 0;
  
  // 初始状态：位置0
  firstPos[{0, 0}] = 0;
  
  int maxLen = 0;
  
  for (int i = 0; i < n; ++i) {
    xorPrefix ^= nums[i];
    if (nums[i] % 2 == 0) {
      evenCount++;
    } else {
      oddCount++;
    }
    
    int diff = evenCount - oddCount;
    pair<int, int> key = {xorPrefix, diff};
    
    if (firstPos.find(key) != firstPos.end()) {
      int len = i + 1 - firstPos[key];
      maxLen = max(maxLen, len);
    } else {
      firstPos[key] = i + 1;
    }
  }
  
  return maxLen;
}

FindMaximumBalancedXorSubarrayLengthSolution::FindMaximumBalancedXorSubarrayLengthSolution() {
  setMetaInfo({.id = 3755,
               .title = "Find Maximum Balanced XOR Subarray Length",
               .url = "https://leetcode.com/problems/find-maximum-balanced-xor-subarray-length/"});
  registerStrategy("Prefix XOR + Hash Map (Encoded)", solution1);
  registerStrategy("Prefix XOR + Hash Map (Pair)", solution2);
}

int FindMaximumBalancedXorSubarrayLengthSolution::maxBalancedSubarray(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_3755
}  // namespace leetcode
