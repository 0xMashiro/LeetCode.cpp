#include "leetcode/problems/maximum-level-sum-of-a-binary-tree.h"

namespace leetcode {
namespace problem_1161 {

// BFS 层次遍历
// 时间复杂度: O(n), 空间复杂度: O(w) w为树的最大宽度
static int solution1(TreeNode* root) {
    if (!root) return 0;
    queue<TreeNode*> q;
    q.push(root);
    int level = 1;
    int maxSum = INT_MIN;
    int resultLevel = 1;
    while (!q.empty()) {
        int size = q.size();
        int sum = 0;
        for (int i = 0; i < size; ++i) {
            TreeNode* node = q.front();
            q.pop();
            sum += node->val;
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        if (sum > maxSum) {
            maxSum = sum;
            resultLevel = level;
        }
        ++level;
    }
    return resultLevel;
}

// DFS 递归遍历
// 时间复杂度: O(n), 空间复杂度: O(h) h为树的高度，加上存储每层和的 O(L)
static int solution2(TreeNode* root) {
    vector<int> levelSums;
    function<void(TreeNode*, int)> dfs = [&](TreeNode* node, int level) {
        if (!node) return;
        if (levelSums.size() < level) {
            levelSums.resize(level);
        }
        levelSums[level - 1] += node->val;
        dfs(node->left, level + 1);
        dfs(node->right, level + 1);
    };
    dfs(root, 1);
    int maxSum = INT_MIN;
    int resultLevel = 1;
    for (int i = 0; i < levelSums.size(); ++i) {
        if (levelSums[i] > maxSum) {
            maxSum = levelSums[i];
            resultLevel = i + 1;
        }
    }
    return resultLevel;
}

MaximumLevelSumOfABinaryTreeSolution::MaximumLevelSumOfABinaryTreeSolution() {
    setMetaInfo({.id = 1161,
                 .title = "Maximum Level Sum of a Binary Tree",
                 .url = "https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree"});
    registerStrategy("BFS", solution1);
    registerStrategy("DFS", solution2);
}

int MaximumLevelSumOfABinaryTreeSolution::maxLevelSum(TreeNode* root) {
    return getSolution()(root);
}

}  // namespace problem_1161
}  // namespace leetcode