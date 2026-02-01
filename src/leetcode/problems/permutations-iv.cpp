
#include "leetcode/problems/permutations-iv.h"

namespace leetcode {
namespace problem_3470 {

// 计算阶乘，上限为 2e15（确保能比较 k 的大小）
static long long safeFact(int x) {
  if (x < 0) return 1;
  long long res = 1;
  for (int i = 2; i <= x; i++) {
    res *= i;
    if (res > (long long)2e15) return (long long)2e15;
  }
  return res;
}

// 计算 count = a * b，带溢出保护
static long long safeMul(long long a, long long b) {
  if (a == 0 || b == 0) return 1;
  if (a > (long long)2e15 / b) return (long long)2e15;
  return a * b;
}

// 主解法：康托展开思想构造第 k 个交替排列
static vector<int> solution(int n, long long k) {
  int oddCount = (n + 1) / 2;   // 奇数个数: 1, 3, 5, ...
  int evenCount = n / 2;        // 偶数个数: 2, 4, 6, ...
  
  // 计算以某个奇数开头的排列数
  long long oddFirstCount = safeMul(safeFact(oddCount - 1), safeFact(evenCount));
  // 计算以某个偶数开头的排列数
  long long evenFirstCount = safeMul(safeFact(oddCount), safeFact(evenCount - 1));
  
  // 计算总排列数
  long long total = safeMul(oddFirstCount, oddCount) + safeMul(evenFirstCount, evenCount);
  if (k > total) return {};
  
  // 准备可用的奇数和偶数列表（保持有序）
  vector<int> odds, evens;
  for (int i = 1; i <= n; i += 2) odds.push_back(i);
  for (int i = 2; i <= n; i += 2) evens.push_back(i);
  
  // 确定第一个位置的可选奇偶性
  // n 为奇数时，必须从数量多的那种开始
  bool canStartWithOdd = (n % 2 == 0) ? true : (oddCount > evenCount);
  bool canStartWithEven = (n % 2 == 0) ? true : (evenCount > oddCount);
  
  vector<int> res;
  
  // 选择第一个数字
  // 构建候选列表：(值, 是否奇数, 在原列表中的索引)
  vector<tuple<int, bool, int>> candidates;
  for (int i = 0; i < (int)odds.size(); i++) {
    if (canStartWithOdd) {
      candidates.push_back({odds[i], true, i});
    }
  }
  for (int i = 0; i < (int)evens.size(); i++) {
    if (canStartWithEven) {
      candidates.push_back({evens[i], false, i});
    }
  }
  // 按值排序
  sort(candidates.begin(), candidates.end());
  
  bool found = false;
  for (auto& [val, isOdd, idx] : candidates) {
    // 计算以这个数字开头的排列数
    long long count = isOdd ? oddFirstCount : evenFirstCount;
    
    if (k > count) {
      k -= count;
    } else {
      // 选择这个数字
      res.push_back(val);
      if (isOdd) {
        odds.erase(odds.begin() + idx);
      } else {
        evens.erase(evens.begin() + idx);
      }
      found = true;
      break;
    }
  }
  
  if (!found) return {};
  
  // 后续位置，奇偶性必须交替
  bool needOdd = (res[0] % 2 == 0);  // 第一个如果是偶数，第二个需要奇数
  
  while (res.size() < (size_t)n) {
    vector<int>& curList = needOdd ? odds : evens;
    int remainingOdd = (int)odds.size();
    int remainingEven = (int)evens.size();
    
    found = false;
    for (size_t i = 0; i < curList.size(); i++) {
      long long count;
      if (needOdd) {
        count = safeMul(safeFact(remainingOdd - 1), safeFact(remainingEven));
      } else {
        count = safeMul(safeFact(remainingOdd), safeFact(remainingEven - 1));
      }
      
      if (k > count) {
        k -= count;
      } else {
        res.push_back(curList[i]);
        curList.erase(curList.begin() + i);
        found = true;
        break;
      }
    }
    
    if (!found) return {};
    needOdd = !needOdd;
  }
  
  return res;
}

PermutationsIvSolution::PermutationsIvSolution() {
  setMetaInfo({.id = 3470,
               .title = "Permutations IV",
               .url = "https://leetcode.com/problems/permutations-iv/"});
  registerStrategy("Cantor Expansion", solution);
}

vector<int> PermutationsIvSolution::permute(int n, long long k) {
  return getSolution()(n, k);
}

}  // namespace problem_3470
}  // namespace leetcode
