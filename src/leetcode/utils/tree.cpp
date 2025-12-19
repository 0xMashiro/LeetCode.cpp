#include "leetcode/utils/tree.h"

#include <climits>
#include <functional>
#include <queue>

namespace leetcode {
TreeNode* constructTree(std::vector<int> values) {
  if (values.empty()) {
    return nullptr;
  }
  TreeNode* root = new TreeNode(values[0]);
  std::queue<TreeNode*> queue;
  queue.push(root);
  int i = 1;
  while (i < values.size()) {
    TreeNode* node = queue.front();
    queue.pop();
    if (values[i] != -1) {
      node->left = new TreeNode(values[i]);
      queue.push(node->left);
    }
    i++;
    if (i < values.size() && values[i] != -1) {
      node->right = new TreeNode(values[i]);
      queue.push(node->right);
    }
    i++;
  }
  return root;
}

TreeNode* constructTree(std::vector<std::optional<int>> values) {
  if (values.empty()) {
    return nullptr;
  }
  TreeNode* root = new TreeNode(values[0].value());
  std::queue<TreeNode*> queue;
  queue.push(root);
  int i = 1;
  while (i < values.size()) {
    TreeNode* node = queue.front();
    queue.pop();
    if (values[i].has_value()) {
      node->left = new TreeNode(values[i].value());
      queue.push(node->left);
    }
    i++;
    if (i < values.size() && values[i].has_value()) {
      node->right = new TreeNode(values[i].value());
      queue.push(node->right);
    }
    i++;
  }
  return root;
}

std::vector<int> preorderTraversal(TreeNode* root) {
  std::vector<int> result;
  std::vector<TreeNode*> stack;
  while (root || !stack.empty()) {
    while (root) {
      result.push_back(root->val);
      stack.push_back(root);
      root = root->left;
    }
    root = stack.back();
    stack.pop_back();
    root = root->right;
  }
  return result;
}

std::vector<int> inorderTraversal(TreeNode* root) {
  std::vector<int> result;
  std::vector<TreeNode*> stack;
  while (root || !stack.empty()) {
    while (root) {
      stack.push_back(root);
      root = root->left;
    }
    root = stack.back();
    stack.pop_back();
    result.push_back(root->val);
    root = root->right;
  }
  return result;
}

std::vector<int> postorderTraversal(TreeNode* root) {
  std::vector<int> result;
  std::vector<TreeNode*> stack;
  TreeNode* prev = nullptr;  // Previous visited node.
  while (root || !stack.empty()) {
    while (root) {
      stack.push_back(root);
      root = root->left;
    }
    root = stack.back();
    if (!root->right || root->right == prev) {
      result.push_back(root->val);
      stack.pop_back();
      prev = root;
      root = nullptr;
    } else {
      root = root->right;
    }
  }
  return result;
}

std::vector<int> levelOrderTraversal(TreeNode* root) {
  std::vector<int> result;
  std::vector<TreeNode*> queue;
  if (root) {
    queue.push_back(root);
  }
  while (!queue.empty()) {
    std::vector<TreeNode*> nextQueue;
    for (TreeNode* node : queue) {
      result.push_back(node->val);
      if (node->left) {
        nextQueue.push_back(node->left);
      }
      if (node->right) {
        nextQueue.push_back(node->right);
      }
    }
    queue = nextQueue;
  }
  return result;
}

std::vector<std::vector<int>> levelOrder(TreeNode* root) {
  std::vector<std::vector<int>> result;
  std::vector<TreeNode*> queue;
  if (root) {
    queue.push_back(root);
  }
  while (!queue.empty()) {
    std::vector<int> levelNode;
    std::vector<TreeNode*> nextQueue;
    for (TreeNode* node : queue) {
      levelNode.push_back(node->val);
      if (node->left) {
        nextQueue.push_back(node->left);
      }
      if (node->right) {
        nextQueue.push_back(node->right);
      }
    }
    result.push_back(levelNode);
    queue = nextQueue;
  }
  return result;
}

TreeNode* invertTree(TreeNode* root) {
  if (root) {
    TreeNode* leftSubTree = root->left;
    root->left = invertTree(root->right);
    root->right = invertTree(leftSubTree);
  }
  return root;
}

bool isSameTree(TreeNode* p, TreeNode* q) {
  if (p == nullptr && q == nullptr) {
    return true;
  }
  if (p == nullptr || q == nullptr) {
    return false;
  }
  return p->val == q->val && isSameTree(p->left, q->left) &&
         isSameTree(p->right, q->right);
}

bool isBST(TreeNode* root) {
  std::vector<int> inorder = inorderTraversal(root);
  for (int i = 1; i < inorder.size(); i++) {
    if (inorder[i] <= inorder[i - 1]) {
      return false;
    }
  }
  return true;
}

bool isBBST(TreeNode* root) {
  std::function<bool(TreeNode*, int, int)> isBBSTHelper =
      [&](TreeNode* node, int lower, int upper) -> bool {
    if (node == nullptr) return true;
    if (node->val <= lower || node->val >= upper) return false;
    return isBBSTHelper(node->left, lower, node->val) &&
           isBBSTHelper(node->right, node->val, upper);
  };
  return isBBSTHelper(root, INT_MIN, INT_MAX);
}
}  // namespace leetcode