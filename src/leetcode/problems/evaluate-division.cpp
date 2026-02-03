#include "leetcode/problems/evaluate-division.h"

namespace leetcode {
namespace problem_399 {

// DFS搜索从start到end的路径，返回权重乘积
static double dfs(const string& start, const string& end, 
                  const unordered_map<string, vector<pair<string, double>>>& graph,
                  unordered_set<string>& visited) {
  // 起点不在图中
  if (graph.find(start) == graph.end()) {
    return -1.0;
  }
  
  // 找到终点
  if (start == end) {
    return 1.0;
  }
  
  visited.insert(start);
  
  // 遍历邻接节点
  for (const auto& [neighbor, weight] : graph.at(start)) {
    if (visited.find(neighbor) != visited.end()) {
      continue;
    }
    
    double result = dfs(neighbor, end, graph, visited);
    if (result != -1.0) {
      return weight * result;
    }
  }
  
  return -1.0;
}

static vector<double> solution1(vector<vector<string>>& equations, 
                                 vector<double>& values, 
                                 vector<vector<string>>& queries) {
  // 构建图
  unordered_map<string, vector<pair<string, double>>> graph;
  
  for (size_t i = 0; i < equations.size(); ++i) {
    const string& a = equations[i][0];
    const string& b = equations[i][1];
    double value = values[i];
    
    graph[a].push_back({b, value});
    graph[b].push_back({a, 1.0 / value});
  }
  
  // 处理每个查询
  vector<double> results;
  results.reserve(queries.size());
  
  for (const auto& query : queries) {
    const string& c = query[0];
    const string& d = query[1];
    
    // 检查变量是否在图中
    if (graph.find(c) == graph.end() || graph.find(d) == graph.end()) {
      results.push_back(-1.0);
      continue;
    }
    
    // 特殊情况：c == d
    if (c == d) {
      results.push_back(1.0);
      continue;
    }
    
    // DFS搜索路径
    unordered_set<string> visited;
    double result = dfs(c, d, graph, visited);
    results.push_back(result);
  }
  
  return results;
}

EvaluateDivisionSolution::EvaluateDivisionSolution() {
  setMetaInfo({
    .id = 399,
    .title = "Evaluate Division",
    .url = "https://leetcode.com/problems/evaluate-division/"
  });
  registerStrategy("DFS", solution1);
}

vector<double> EvaluateDivisionSolution::calcEquation(
    vector<vector<string>>& equations, 
    vector<double>& values, 
    vector<vector<string>>& queries) {
  return getSolution()(equations, values, queries);
}

}  // namespace problem_399
}  // namespace leetcode
