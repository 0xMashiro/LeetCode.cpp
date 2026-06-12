#include "leetcode/problems/split-the-array-to-make-coprime-products.h"

namespace leetcode {
namespace problem_2584 {

// 埃氏筛：预处理每个数的最小质因子
const int MAXN = 1000000;
static vector<int> get_spf() {
  static vector<int> spf(MAXN + 1, 0);
  static bool initialized = false;
  if (initialized) return spf;
  initialized = true;
  for (int i = 0; i <= MAXN; ++i) spf[i] = i;
  for (int i = 2; i * i <= MAXN; ++i) {
    if (spf[i] == i) {  // i is prime
      for (int j = i * i; j <= MAXN; j += i) {
        if (spf[j] == j) spf[j] = i;
      }
    }
  }
  return spf;
}

// 用 spf 分解质因子（去重）
static vector<int> get_prime_factors(int x) {
  static vector<int> spf = get_spf();
  vector<int> res;
  while (x > 1) {
    int p = spf[x];
    res.push_back(p);
    while (x % p == 0) x /= p;
  }
  return res;
}

static int solution1(vector<int>& nums) {
  int n = (int)nums.size();
  if (n <= 1) return -1;
  
  // 第一遍：记录每个质因子第一次和最后一次出现的位置
  unordered_map<int, int> first_occ, last_occ;
  for (int i = 0; i < n; ++i) {
    auto factors = get_prime_factors(nums[i]);
    for (int p : factors) {
      if (first_occ.find(p) == first_occ.end()) {
        first_occ[p] = i;
      }
      last_occ[p] = i;
    }
  }
  
  // 第二遍：扫描，维护当前区间右端点
  int cur_right = 0;
  for (int i = 0; i < n; ++i) {
    auto factors = get_prime_factors(nums[i]);
    for (int p : factors) {
      // 这个质因子的区间必须全部在左半部分或全部在右半部分
      // 它的 last_occ 决定了左半部分至少要延伸到 last_occ[p]
      cur_right = max(cur_right, last_occ[p]);
    }
    // 当 i == cur_right 且 i < n-1 时，可以在 i 处分割
    if (i == cur_right && i < n - 1) {
      return i;
    }
  }
  
  return -1;
}

SplitTheArrayToMakeCoprimeProductsSolution::SplitTheArrayToMakeCoprimeProductsSolution() {
  setMetaInfo({
      .id = 2584,
      .title = "Split the Array to Make Coprime Products",
      .url = "https://leetcode.com/problems/split-the-array-to-make-coprime-products"
  });
  registerStrategy({.name = "Brute Force"}, solution1);
}

int SplitTheArrayToMakeCoprimeProductsSolution::findValidSplit(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_2584
}  // namespace leetcode
