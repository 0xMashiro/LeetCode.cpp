#include "leetcode/problems/n-ary-tree-preorder-traversal.h"

namespace leetcode {
namespace problem_589 {

//! Construct an N-ary tree from level order representation.
//! null values in the vector represent separators between groups of children.
Node* constructNaryTree(const vector<optional<int>>& values) {
  if (values.empty() || !values[0].has_value()) {
    return nullptr;
  }

  Node* root = new Node(values[0].value());
  queue<Node*> q;
  q.push(root);

  size_t i = 2;  // Start after root and first null separator
  while (!q.empty() && i < values.size()) {
    Node* current = q.front();
    q.pop();

    // Process all children for current node until next null
    while (i < values.size() && values[i].has_value()) {
      Node* child = new Node(values[i].value());
      current->children.push_back(child);
      q.push(child);
      i++;
    }

    // Skip the null separator
    i++;
  }

  return root;
}

//! Recursive solution: DFS preorder traversal
//! Time Complexity: O(n), Space Complexity: O(h) where h is height
static vector<int> solution1(Node* root) {
  vector<int> result;

  function<void(Node*)> dfs = [&](Node* node) {
    if (!node) return;
    result.push_back(node->val);
    for (Node* child : node->children) {
      dfs(child);
    }
  };

  dfs(root);
  return result;
}

//! Iterative solution: Using stack to simulate recursion
//! Time Complexity: O(n), Space Complexity: O(h)
static vector<int> solution2(Node* root) {
  if (!root) return {};

  vector<int> result;
  vector<Node*> stack;
  stack.push_back(root);

  while (!stack.empty()) {
    Node* node = stack.back();
    stack.pop_back();
    result.push_back(node->val);

    // Push children in reverse order so that first child is processed first
    for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
      if (*it) {
        stack.push_back(*it);
      }
    }
  }

  return result;
}

NAryTreePreorderTraversalSolution::NAryTreePreorderTraversalSolution() {
  setMetaInfo({.id = 589,
               .title = "N-ary Tree Preorder Traversal",
               .url = "https://leetcode.com/problems/n-ary-tree-preorder-traversal/"});
  registerStrategy("Recursive DFS", solution1);
  registerStrategy("Iterative Stack", solution2);
}

vector<int> NAryTreePreorderTraversalSolution::preorder(Node* root) {
  return getSolution()(root);
}

}  // namespace problem_589
}  // namespace leetcode
