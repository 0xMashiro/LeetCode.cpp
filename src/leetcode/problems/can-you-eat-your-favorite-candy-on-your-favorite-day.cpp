#include "leetcode/problems/can-you-eat-your-favorite-candy-on-your-favorite-day.h"

namespace leetcode {
namespace problem_1744 {

/**
 * 解题思路：
 * 1. 计算前缀和 prefixSum，其中 prefixSum[i] 表示前 i-1 种糖果的累计数量
 *    即 prefixSum[0] = 0, prefixSum[1] = candiesCount[0], ...
 * 
 * 2. 对于查询 [favoriteType, favoriteDay, dailyCap]：
 *    - 第 favoriteType 种糖果的索引范围是 [prefixSum[favoriteType], prefixSum[favoriteType+1] - 1]
 *    
 *    - 最早吃到第 favoriteType 种糖果的情况：每天吃 dailyCap 颗
 *      最早在第 prefixSum[favoriteType] / dailyCap 天吃到
 *    
 *    - 最晚吃到第 favoriteType 种糖果的情况：每天吃 1 颗
 *      最晚在第 prefixSum[favoriteType+1] - 1 天吃到
 *    
 *    - 判断条件：
 *      a) 第 favoriteDay 天还没吃完前 favoriteType+1 种糖果：favoriteDay < prefixSum[favoriteType+1]
 *      b) 第 favoriteDay 天之前已经吃完前 favoriteType 种糖果：(long long)favoriteDay * dailyCap >= prefixSum[favoriteType]
 * 
 * 时间复杂度：O(n + q)，其中 n 是 candiesCount 长度，q 是 queries 长度
 * 空间复杂度：O(n)
 */
static vector<bool> solution1(vector<int>& candiesCount, vector<vector<int>>& queries) {
  int n = candiesCount.size();
  int q = queries.size();
  
  // 计算前缀和
  vector<long long> prefixSum(n + 1, 0);
  for (int i = 0; i < n; ++i) {
    prefixSum[i + 1] = prefixSum[i] + candiesCount[i];
  }
  
  vector<bool> answer;
  answer.reserve(q);
  
  for (const auto& query : queries) {
    int favoriteType = query[0];
    int favoriteDay = query[1];
    long long dailyCap = query[2];
    
    // 第 favoriteType 种糖果的起始索引（包含）
    long long start = prefixSum[favoriteType];
    // 第 favoriteType 种糖果的结束索引（不包含）
    long long end = prefixSum[favoriteType + 1];
    
    // 第 favoriteDay 天最少能吃 favoriteDay + 1 颗糖果（每天至少1颗，从第0天开始）
    // 第 favoriteDay 天最多能吃 (favoriteDay + 1) * dailyCap 颗糖果
    
    // 条件1：第 favoriteDay 天还没吃完前 favoriteType+1 种糖果
    // 即：favoriteDay + 1 <= end  或者 favoriteDay < end
    // 因为从第0天开始，第d天累计至少吃了d+1颗糖果
    // 实际上是：favoriteDay + 1 <= end，因为到第d天至少吃了d+1颗
    // 等价于：favoriteDay < end
    bool condition1 = (long long)favoriteDay < end;
    
    // 条件2：第 favoriteDay 天之前已经吃完前 favoriteType 种糖果
    // 即：在第d天之前，以最大速度 eating，能吃完前 favoriteType 种
    // 到第d天累计最多能吃 (favoriteDay + 1) * dailyCap 颗
    // 需要 (favoriteDay + 1) * dailyCap > start
    // 或者理解为：favoriteDay * dailyCap >= start（因为第d天可以吃新类型的糖果）
    bool condition2 = (long long)(favoriteDay + 1) * dailyCap > start;
    
    answer.push_back(condition1 && condition2);
  }
  
  return answer;
}

CanYouEatYourFavoriteCandyOnYourFavoriteDaySolution::CanYouEatYourFavoriteCandyOnYourFavoriteDaySolution() {
  setMetaInfo({
    .id = 1744,
    .title = "Can You Eat Your Favorite Candy on Your Favorite Day?",
    .url = "https://leetcode.com/problems/can-you-eeat-your-favorite-candy-on-your-favorite-day/"
  });
  registerStrategy("Prefix Sum", solution1);
}

vector<bool> CanYouEatYourFavoriteCandyOnYourFavoriteDaySolution::canEat(
    vector<int>& candiesCount, vector<vector<int>>& queries) {
  return getSolution()(candiesCount, queries);
}

}  // namespace problem_1744
}  // namespace leetcode
