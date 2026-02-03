#include "leetcode/core.h"

namespace leetcode {
namespace problem_1600 {

/**
 * Throne Inheritance 实现
 * 思路：使用多叉树存储家族关系，用哈希表记录子女列表和死亡状态
 * - children_: 存储每个人的子女列表（vector保持出生顺序）
 * - dead_: 存储死亡人员的集合
 * - kingName_: 国王名字，作为树的根节点
 * 
 * birth: O(1) 将子女添加到父母的列表末尾
 * death: O(1) 将人员标记为死亡
 * getInheritanceOrder: O(n) DFS前序遍历，跳过死亡人员
 */
class ThroneInheritance {
 public:
  ThroneInheritance(string kingName);

  void birth(string parentName, string childName);

  void death(string name);

  vector<string> getInheritanceOrder();

 private:
  // DFS遍历辅助函数
  void dfs(const string& name, vector<string>& result);

  string kingName_;
  unordered_map<string, vector<string>> children_;  // 子女列表
  unordered_set<string> dead_;  // 死亡人员集合
};

}  // namespace problem_1600
}  // namespace leetcode
