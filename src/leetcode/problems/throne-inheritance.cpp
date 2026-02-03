#include "leetcode/problems/throne-inheritance.h"

namespace leetcode {
namespace problem_1600 {

ThroneInheritance::ThroneInheritance(string kingName) 
    : kingName_(std::move(kingName)) {}

void ThroneInheritance::birth(string parentName, string childName) {
  children_[parentName].push_back(std::move(childName));
}

void ThroneInheritance::death(string name) {
  dead_.insert(std::move(name));
}

vector<string> ThroneInheritance::getInheritanceOrder() {
  vector<string> result;
  dfs(kingName_, result);
  return result;
}

void ThroneInheritance::dfs(const string& name, vector<string>& result) {
  // 如果当前人未死亡，加入结果
  if (dead_.find(name) == dead_.end()) {
    result.push_back(name);
  }
  
  // 递归遍历所有子女（按出生顺序）
  auto it = children_.find(name);
  if (it != children_.end()) {
    for (const auto& child : it->second) {
      dfs(child, result);
    }
  }
}

}  // namespace problem_1600
}  // namespace leetcode
