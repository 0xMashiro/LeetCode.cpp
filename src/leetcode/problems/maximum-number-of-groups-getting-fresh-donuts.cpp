#include "leetcode/problems/maximum-number-of-groups-getting-fresh-donuts.h"

namespace leetcode {
namespace problem_1815 {

class Solution {
 public:
  int maxHappyGroups(int batchSize, vector<int>& groups) {
    this->batchSize = batchSize;
    
    // 统计每个余数的出现次数
    vector<int> cnt(batchSize, 0);
    for (int g : groups) {
      cnt[g % batchSize]++;
    }
    
    // 余数为0的组总是快乐的
    int happy = cnt[0];
    cnt[0] = 0;
    
    // 对于 i 和 batchSize-i 的配对，优先组合它们
    // 这样可以减少状态空间，优化搜索
    for (int i = 1; i <= batchSize / 2; ++i) {
      if (i == batchSize - i) {
        // 例如 batchSize=4, i=2 的情况
        happy += cnt[i] / 2;
        cnt[i] %= 2;
      } else {
        int pairs = min(cnt[i], cnt[batchSize - i]);
        happy += pairs;
        cnt[i] -= pairs;
        cnt[batchSize - i] -= pairs;
      }
    }
    
    // 使用记忆化搜索求解剩余部分
    // 状态编码：用 (batchSize) 进制数表示各余数的剩余数量
    memo.clear();
    int state = encode(cnt);
    happy += dfs(state, 0);
    
    return happy;
  }
  
 private:
  int batchSize;
  unordered_map<long long, int> memo;
  
  // 将计数数组编码为状态
  long long encode(const vector<int>& cnt) {
    long long state = 0;
    for (int i = batchSize - 1; i >= 0; --i) {
      state = state * 6 + cnt[i];  // 用6进制（因为每组最多30个，但配对后数量很少）
    }
    return state;
  }
  
  // 将状态解码为计数数组
  vector<int> decode(long long state) {
    vector<int> cnt(batchSize, 0);
    for (int i = 0; i < batchSize; ++i) {
      cnt[i] = state % 6;
      state /= 6;
    }
    return cnt;
  }
  
  // 记忆化搜索
  // state: 当前各余数的剩余数量编码
  // remainder: 当前批次的剩余位置（即当前已经用了 batchSize - remainder 个）
  // 返回值：从当前状态开始还能获得的最大快乐组数
  int dfs(long long state, int remainder) {
    if (state == 0) return 0;
    
    long long key = state * batchSize + remainder;
    if (memo.count(key)) return memo[key];
    
    vector<int> cnt = decode(state);
    int res = 0;
    
    for (int i = 1; i < batchSize; ++i) {
      if (cnt[i] > 0) {
        cnt[i]--;
        int newState = encode(cnt);
        int newRemainder = (remainder + i) % batchSize;
        // 如果 remainder == 0，说明这组是快乐的
        int happy = (remainder == 0) ? 1 : 0;
        res = max(res, happy + dfs(newState, newRemainder));
        cnt[i]++;
      }
    }
    
    memo[key] = res;
    return res;
  }
};

// 主解法：状态压缩记忆化搜索
static int solution1(int batchSize, vector<int>& groups) {
  Solution sol;
  return sol.maxHappyGroups(batchSize, groups);
}

MaximumNumberOfGroupsGettingFreshDonutsSolution::MaximumNumberOfGroupsGettingFreshDonutsSolution() {
  setMetaInfo({.id = 1815,
               .title = "Maximum Number of Groups Getting Fresh Donuts",
               .url = "https://leetcode.com/problems/maximum-number-of-groups-getting-fresh-donuts/"});
  registerStrategy("Memoization Search", solution1);
}

int MaximumNumberOfGroupsGettingFreshDonutsSolution::maxHappyGroups(int batchSize, vector<int>& groups) {
  return getSolution()(batchSize, groups);
}

}  // namespace problem_1815
}  // namespace leetcode
