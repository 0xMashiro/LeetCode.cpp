#include "leetcode/problems/unique-binary-search-trees-ii.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_95 {

class UniqueBinarySearchTreesIiTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  UniqueBinarySearchTreesIiSolution solution;
};

/**
 * @brief 辅助函数：获取树的中序遍历结果（BST 的中序遍历是有序的）
 */
static std::vector<int> getInorder(TreeNode* root) {
  std::vector<int> result;
  std::function<void(TreeNode*)> inorder = [&](TreeNode* node) {
    if (!node) return;
    inorder(node->left);
    result.push_back(node->val);
    inorder(node->right);
  };
  inorder(root);
  return result;
}

/**
 * @brief 辅助函数：验证是否是有效的 BST
 */
static bool isValidBST(TreeNode* root, long minVal = LONG_MIN, long maxVal = LONG_MAX) {
  if (!root) return true;
  if (root->val <= minVal || root->val >= maxVal) return false;
  return isValidBST(root->left, minVal, root->val) &&
         isValidBST(root->right, root->val, maxVal);
}

/**
 * @brief 辅助函数：获取树的结构表示（用于比较）
 * 使用前序遍历序列化，null 用 -1 表示
 */
static std::string serialize(TreeNode* root) {
  if (!root) return "#";
  return std::to_string(root->val) + "," + 
         serialize(root->left) + "," + 
         serialize(root->right);
}

TEST_P(UniqueBinarySearchTreesIiTest, Example1_nEquals3) {
  int n = 3;
  vector<TreeNode*> result = solution.generateTrees(n);
  
  // n=3 应该有 5 种不同的 BST（第3个卡特兰数）
  EXPECT_EQ(result.size(), 5);
  
  // 验证每棵树都是有效的 BST
  for (TreeNode* tree : result) {
    EXPECT_TRUE(isValidBST(tree));
    // 验证中序遍历是 [1,2,3]
    std::vector<int> inorder = getInorder(tree);
    EXPECT_EQ(inorder.size(), 3);
    EXPECT_EQ(inorder, std::vector<int>({1, 2, 3}));
  }
  
  // 验证所有树结构唯一
  std::set<std::string> structures;
  for (TreeNode* tree : result) {
    structures.insert(serialize(tree));
  }
  EXPECT_EQ(structures.size(), 5);
}

TEST_P(UniqueBinarySearchTreesIiTest, Example2_nEquals1) {
  int n = 1;
  vector<TreeNode*> result = solution.generateTrees(n);
  
  // n=1 只有 1 种 BST
  EXPECT_EQ(result.size(), 1);
  EXPECT_TRUE(isValidBST(result[0]));
  EXPECT_EQ(getInorder(result[0]), std::vector<int>({1}));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, UniqueBinarySearchTreesIiTest,
    ::testing::ValuesIn(UniqueBinarySearchTreesIiSolution().getStrategyNames()));

}  // namespace problem_95
}  // namespace leetcode
