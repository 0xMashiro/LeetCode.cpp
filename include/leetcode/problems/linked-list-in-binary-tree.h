
#include "leetcode/core.h"

namespace leetcode {
namespace problem_1367 {

using Func = std::function<bool(ListNode*, TreeNode*)>;

class LinkedListInBinaryTreeSolution : public SolutionBase<Func> {
 public:
  //! 1367. Linked List in Binary Tree
  //! https://leetcode.com/problems/linked-list-in-binary-tree/
  bool isSubPath(ListNode* head, TreeNode* root);

  LinkedListInBinaryTreeSolution();
};

}  // namespace problem_1367
}  // namespace leetcode
