#include "leetcode/problems/stamping-the-sequence.h"

namespace leetcode {
namespace problem_936 {

static vector<int> solution1(string stamp, string target) {
  int m = stamp.size(), n = target.size();
  vector<int> result;
  vector<char> t(target.begin(), target.end());
  vector<bool> done(n, false);
  
  // 贪心逆向模拟：尝试找到可以取消盖章的位置
  int total = 0;
  while (total < n) {
    bool found = false;
    for (int i = 0; i <= n - m; ++i) {
      if (done[i]) continue;
      // 检查 target[i..i+m-1] 是否能被 stamp 覆盖
      bool can_stamp = true;
      int stamped_count = 0;
      for (int j = 0; j < m; ++j) {
        if (t[i + j] == '?') continue;  // 已被还原
        if (t[i + j] != stamp[j]) {
          can_stamp = false;
          break;
        }
        ++stamped_count;
      }
      if (!can_stamp || stamped_count == 0) continue;
      
      // 可以盖章，将这段全部变成 '?'
      found = true;
      done[i] = true;
      for (int j = 0; j < m; ++j) {
        if (t[i + j] != '?') {
          t[i + j] = '?';
          ++total;
        }
      }
      result.push_back(i);
    }
    if (!found) break;
  }
  
  if (total != n) return {};  // 无法还原成全 '?'
  
  // 反转操作序列
  reverse(result.begin(), result.end());
  return result;
}

StampingTheSequenceSolution::StampingTheSequenceSolution() {
  setMetaInfo({
      .id = 936,
      .title = "Stamping The Sequence",
      .url = "https://leetcode.com/problems/stamping-the-sequence"
  });
  registerStrategy({.name = "Brute Force"}, solution1);
}

vector<int> StampingTheSequenceSolution::movesToStamp(string stamp, string target) {
  return getSolution()(stamp, target);
}

}  // namespace problem_936
}  // namespace leetcode
