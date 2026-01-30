#include "leetcode/problems/minimum-cost-to-convert-string-ii.h"

namespace leetcode {
namespace problem_2977 {

namespace {

const long long INF = 1LL << 60;  // 足够大的值

// 滚动哈希实现，使用单哈希（base=131, mod=1e9+7）
class RollingHash {
 public:
  RollingHash(const std::string& s) {
    n_ = s.size();
    hash_.resize(n_ + 1);
    hash_[0] = 0;
    const long long base = 131;
    const long long mod = 1000000007;
    pow_.resize(n_ + 1);
    pow_[0] = 1;
    for (int i = 0; i < n_; ++i) {
      hash_[i + 1] = (hash_[i] * base + s[i]) % mod;
      pow_[i + 1] = (pow_[i] * base) % mod;
    }
  }

  // 返回子串 [l, r) 的哈希值
  long long get(int l, int r) const {
    const long long mod = 1000000007;
    long long res = (hash_[r] - hash_[l] * pow_[r - l]) % mod;
    if (res < 0) res += mod;
    return res;
  }

 private:
  int n_;
  std::vector<long long> hash_;
  std::vector<long long> pow_;
};

// 策略1：动态规划 + 最短路径 + 字符串哈希
static long long solution1(std::string source, std::string target,
                           std::vector<std::string>& original,
                           std::vector<std::string>& changed,
                           std::vector<int>& cost) {
  int n = source.size();
  int m = original.size();  // 转换规则数量

  // 步骤1：收集所有字符串节点
  std::unordered_map<std::string, int> str_to_idx;
  auto get_index = [&](const std::string& s) {
    auto it = str_to_idx.find(s);
    if (it != str_to_idx.end()) return it->second;
    int idx = str_to_idx.size();
    str_to_idx[s] = idx;
    return idx;
  };

  // 初始化所有字符串的索引
  for (int i = 0; i < m; ++i) {
    get_index(original[i]);
    get_index(changed[i]);
  }

  int node_count = str_to_idx.size();
  // 步骤2：初始化距离矩阵
  std::vector<std::vector<long long>> dist(
      node_count, std::vector<long long>(node_count, INF));
  for (int i = 0; i < node_count; ++i) dist[i][i] = 0;

  for (int i = 0; i < m; ++i) {
    int u = str_to_idx[original[i]];
    int v = str_to_idx[changed[i]];
    long long w = cost[i];
    if (w < dist[u][v]) dist[u][v] = w;
  }

  // 步骤3：Floyd-Warshall 计算所有节点对之间的最短路径
  for (int k = 0; k < node_count; ++k) {
    for (int i = 0; i < node_count; ++i) {
      if (dist[i][k] == INF) continue;
      for (int j = 0; j < node_count; ++j) {
        if (dist[k][j] == INF) continue;
        if (dist[i][k] + dist[k][j] < dist[i][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
        }
      }
    }
  }

  // 步骤4：计算 source 和 target 的滚动哈希
  RollingHash hash_source(source), hash_target(target);

  // 步骤5：为每个节点字符串计算哈希值，并记录在 source 和 target 中的出现位置
  std::vector<std::unordered_map<int, int>> source_matches(n);
  std::vector<std::unordered_map<int, int>> target_matches(n);

  // 预处理每个字符串的哈希值
  std::unordered_map<std::string, long long> str_hash;
  for (const auto& kv : str_to_idx) {
    const std::string& s = kv.first;
    int len = s.size();
    // 计算字符串 s 的哈希值（与 RollingHash 使用相同的参数）
    const long long base = 131;
    const long long mod = 1000000007;
    long long h = 0;
    for (char c : s) {
      h = (h * base + c) % mod;
    }
    str_hash[s] = h;
  }

  // 在 source 中查找匹配
  for (const auto& kv : str_to_idx) {
    const std::string& s = kv.first;
    int idx = kv.second;
    int len = s.size();
    long long h = str_hash[s];
    for (int start = 0; start + len <= n; ++start) {
      if (hash_source.get(start, start + len) == h) {
        // 验证实际字符串（避免哈希冲突）
        if (source.substr(start, len) == s) {
          source_matches[start][len] = idx;
        }
      }
    }
  }

  // 在 target 中查找匹配
  for (const auto& kv : str_to_idx) {
    const std::string& s = kv.first;
    int idx = kv.second;
    int len = s.size();
    long long h = str_hash[s];
    for (int start = 0; start + len <= n; ++start) {
      if (hash_target.get(start, start + len) == h) {
        if (target.substr(start, len) == s) {
          target_matches[start][len] = idx;
        }
      }
    }
  }

  // 步骤6：动态规划
  std::vector<long long> dp(n + 1, INF);
  dp[0] = 0;
  for (int i = 0; i < n; ++i) {
    if (dp[i] == INF) continue;
    // 情况1：跳过当前字符（如果相等）
    if (source[i] == target[i]) {
      dp[i + 1] = std::min(dp[i + 1], dp[i]);
    }
    // 情况2：应用转换
    for (const auto& kv : source_matches[i]) {
      int len = kv.first;
      int u = kv.second;
      auto it = target_matches[i].find(len);
      if (it != target_matches[i].end()) {
        int v = it->second;
        if (dist[u][v] < INF) {
          dp[i + len] = std::min(dp[i + len], dp[i] + dist[u][v]);
        }
      }
    }
  }

  return dp[n] == INF ? -1 : dp[n];
}

}  // namespace

MinimumCostToConvertStringIiSolution::MinimumCostToConvertStringIiSolution() {
  setMetaInfo({.id = 2977,
               .title = "Minimum Cost to Convert String II",
               .url = "https://leetcode.com/problems/minimum-cost-to-convert-string-ii/"});
  registerStrategy("DP with Shortest Path and Rolling Hash", solution1);
}

long long MinimumCostToConvertStringIiSolution::minimumCost(
    std::string source, std::string target, std::vector<std::string>& original,
    std::vector<std::string>& changed, std::vector<int>& cost) {
  return getSolution()(source, target, original, changed, cost);
}

}  // namespace problem_2977
}  // namespace leetcode