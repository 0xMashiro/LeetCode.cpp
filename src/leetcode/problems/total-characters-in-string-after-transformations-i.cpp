#include "leetcode/problems/total-characters-in-string-after-transformations-i.h"

namespace leetcode {
namespace problem_3335 {

static const int MOD = 1e9 + 7;

// 计数法：统计每种字符的数量，进行 t 轮变换
// 时间复杂度: O(26 * t), 空间复杂度: O(26)
static int solution1(string s, int t) {
  // cnt[i] 表示字符 'a' + i 的数量
  vector<long long> cnt(26, 0);
  for (char c : s) {
    cnt[c - 'a']++;
  }

  for (int round = 0; round < t; ++round) {
    // 保存当前 'z' 的数量，因为 'z' 会变成 'a' 和 'b'
    long long zCount = cnt[25];
    
    // 'y' -> 'z', 'x' -> 'y', ..., 'a' -> 'b'
    // 从后往前更新，避免覆盖
    for (int i = 24; i >= 0; --i) {
      cnt[i + 1] = cnt[i];
    }
    
    // 'z' 变成 'a' 和 'b'
    cnt[0] = zCount;  // 变成 'a'
    cnt[1] = (cnt[1] + zCount) % MOD;  // 变成 'b'，注意要加上原来从 'a' 变来的
    
    // 实际上，上述处理有误，重新思考：
    // 本轮新的 'a' 只来自上一轮 'z' 的变换
    // 本轮新的 'b' 来自：上一轮 'a' 变成的 + 上一轮 'z' 变成的
    // 所以需要重新实现
  }

  // 重新实现，更清晰的版本
  // 重置
  fill(cnt.begin(), cnt.end(), 0);
  for (char c : s) {
    cnt[c - 'a']++;
  }

  for (int round = 0; round < t; ++round) {
    // newCnt[i] 表示本轮变换后字符 'a'+i 的数量
    vector<long long> newCnt(26, 0);
    
    for (int i = 0; i < 26; ++i) {
      if (cnt[i] == 0) continue;
      
      if (i == 25) {
        // 'z' 变成 "ab"
        newCnt[0] = (newCnt[0] + cnt[i]) % MOD;  // 'a'
        newCnt[1] = (newCnt[1] + cnt[i]) % MOD;  // 'b'
      } else {
        // 其他字符变成下一个
        newCnt[i + 1] = (newCnt[i + 1] + cnt[i]) % MOD;
      }
    }
    
    cnt = newCnt;
  }

  long long result = 0;
  for (long long x : cnt) {
    result = (result + x) % MOD;
  }
  return static_cast<int>(result);
}

// 优化版本：原地更新，避免每轮创建新数组
static int solution2(string s, int t) {
  vector<long long> cnt(26, 0);
  for (char c : s) {
    cnt[c - 'a']++;
  }

  for (int round = 0; round < t; ++round) {
    // 保存 'z' 的数量
    long long zCount = cnt[25];
    
    // 从 'y' 到 'a'，依次后移
    for (int i = 24; i >= 0; --i) {
      cnt[i + 1] = cnt[i];
    }
    
    // 'z' 变成 'a' 和 'b'
    cnt[0] = zCount;           // 'a'
    cnt[1] = (cnt[1] + zCount) % MOD;  // 'b'（原来的 'a' 已经移到 'b'，再加上 'z' 变来的）
  }

  long long result = 0;
  for (long long x : cnt) {
    result = (result + x) % MOD;
  }
  return static_cast<int>(result);
}

TotalCharactersInStringAfterTransformationsISolution::TotalCharactersInStringAfterTransformationsISolution() {
  setMetaInfo({.id = 3335,
               .title = "Total Characters in String After Transformations I",
               .url = "https://leetcode.com/problems/total-characters-in-string-after-transformations-i/"});
  registerStrategy("Counting", solution1);
  registerStrategy("Optimized Counting", solution2);
}

int TotalCharactersInStringAfterTransformationsISolution::lengthAfterTransformations(string s, int t) {
  return getSolution()(s, t);
}

}  // namespace problem_3335
}  // namespace leetcode