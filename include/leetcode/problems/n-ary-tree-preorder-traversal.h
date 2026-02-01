#include "leetcode/core.h"

namespace leetcode {
namespace problem_589 {

//! Definition for a Node.
class Node {
 public:
  int val;
  vector<Node*> children;

  Node() {}

  Node(int _val) : val(_val) {}

  Node(int _val, vector<Node*> _children) : val(_val), children(_children) {}

  ~Node() {
    for (Node* child : children) {
      delete child;
    }
  }
};

//! Construct an N-ary tree from level order representation.
//! null values in the vector represent separators between groups of children.
Node* constructNaryTree(const vector<optional<int>>& values);

using Func = std::function<vector<int>(Node*)>;

class NAryTreePreorderTraversalSolution : public SolutionBase<Func> {
 public:
  //! 589. N-ary Tree Preorder Traversal
  //! https://leetcode.com/problems/n-ary-tree-preorder-traversal/
  vector<int> preorder(Node* root);

  NAryTreePreorderTraversalSolution();
};

}  // namespace problem_589
}  // namespace leetcode
