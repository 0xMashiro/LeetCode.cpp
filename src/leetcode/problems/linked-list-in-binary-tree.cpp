
#include "leetcode/problems/linked-list-in-binary-tree.h"

namespace leetcode {
namespace problem_1367 {

// 辅助函数：检查从当前树节点开始是否能匹配链表
static bool check(ListNode* head, TreeNode* root) {
  // 链表已全部匹配
  if (head == nullptr) return true;
  // 树节点为空但链表未匹配完
  if (root == nullptr) return false;
  // 当前值不匹配
  if (head->val != root->val) return false;
  // 当前值匹配，继续匹配链表的下一个节点（可以走左子树或右子树）
  return check(head->next, root->left) || check(head->next, root->right);
}

// 主解法：遍历二叉树的每个节点，尝试匹配链表
// 时间复杂度: O(N * min(L, H))，N为树节点数，L为链表长度，H为树高度
// 空间复杂度: O(H)，递归栈深度
static bool solution1(ListNode* head, TreeNode* root) {
  if (root == nullptr) return false;
  // 从当前节点开始匹配，或者继续在左右子树中寻找
  return check(head, root) || solution1(head, root->left) || solution1(head, root->right);
}

LinkedListInBinaryTreeSolution::LinkedListInBinaryTreeSolution() {
  setMetaInfo({.id = 1367,
               .title = "Linked List in Binary Tree",
               .url = "https://leetcode.com/problems/linked-list-in-binary-tree/"});
  registerStrategy("DFS + Pattern Matching", solution1);
}

bool LinkedListInBinaryTreeSolution::isSubPath(ListNode* head, TreeNode* root) {
  return getSolution()(head, root);
}

}  // namespace problem_1367
}  // namespace leetcode
