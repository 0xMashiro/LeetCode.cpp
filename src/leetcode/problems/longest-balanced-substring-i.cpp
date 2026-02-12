#include "leetcode/problems/longest-balanced-substring-i.h"

namespace leetcode {
namespace problem_3713 {

// LeetCode 平台使用的标准 Solution 类
class Solution {
 public:
  int longestBalanced(string s) {
    const int n = s.size();
    int maxLen = 0;
    
    // 前缀和数组：prefix[i][c] 表示 s[0:i-1] 中字符 c 的出现次数
    vector<array<int, 26>> prefix(n + 1);
    for (int i = 0; i < n; ++i) {
      prefix[i + 1] = prefix[i];
      prefix[i + 1][s[i] - 'a']++;
    }
    
    // 枚举所有子串
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j <= n; ++j) {
        // 计算子串 s[i:j] 中每个字符的出现次数
        array<int, 26> count{};
        for (int c = 0; c < 26; ++c) {
          count[c] = prefix[j][c] - prefix[i][c];
        }
        
        // 检查是否平衡：收集所有非零次数，检查是否相同
        int targetCount = -1;
        bool balanced = true;
        for (int c = 0; c < 26; ++c) {
          if (count[c] > 0) {
            if (targetCount == -1) {
              targetCount = count[c];
            } else if (count[c] != targetCount) {
              balanced = false;
              break;
            }
          }
        }
        
        if (balanced && targetCount > 0) {
          maxLen = max(maxLen, j - i);
        }
      }
    }
    
    return maxLen;
  }
};

// 暴力枚举 + 前缀和优化
// 时间复杂度: O(26 * n^2) = O(n^2), 空间复杂度: O(26 * n)
static int solution1(string s) {
  const int n = s.size();
  int maxLen = 0;
  
  // 前缀和数组：prefix[i][c] 表示 s[0:i-1] 中字符 c 的出现次数
  vector<array<int, 26>> prefix(n + 1);
  for (int i = 0; i < n; ++i) {
    prefix[i + 1] = prefix[i];
    prefix[i + 1][s[i] - 'a']++;
  }
  
  // 枚举所有子串
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      // 计算子串 s[i:j] 中每个字符的出现次数
      array<int, 26> count{};
      for (int c = 0; c < 26; ++c) {
        count[c] = prefix[j][c] - prefix[i][c];
      }
      
      // 检查是否平衡：收集所有非零次数，检查是否相同
      int targetCount = -1;
      bool balanced = true;
      for (int c = 0; c < 26; ++c) {
        if (count[c] > 0) {
          if (targetCount == -1) {
            targetCount = count[c];
          } else if (count[c] != targetCount) {
            balanced = false;
            break;
          }
        }
      }
      
      if (balanced && targetCount > 0) {
        maxLen = max(maxLen, j - i);
      }
    }
  }
  
  return maxLen;
}

LongestBalancedSubstringISolution::LongestBalancedSubstringISolution() {
  setMetaInfo({.id = 3713,
               .title = "Longest Balanced Substring I",
               .url = "https://leetcode.com/problems/longest-balanced-substring-i/"});
  registerStrategy("Prefix Sum + Enumeration", solution1);
}

int LongestBalancedSubstringISolution::longestBalanced(string s) {
  return getSolution()(s);
}

}  // namespace problem_3713
}  // namespace leetcode
