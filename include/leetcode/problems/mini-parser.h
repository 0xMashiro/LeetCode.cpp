
#include "leetcode/core.h"

namespace leetcode {
namespace problem_385 {

/**
 * Mini Parser 实现
 * 思路：使用递归解析字符串
 * - 如果字符串不以 '[' 开头，说明是单个整数，直接构造返回
 * - 如果字符串以 '[' 开头，解析列表内容，递归处理嵌套结构
 * 时间复杂度：O(n)，n 为字符串长度
 * 空间复杂度：O(d)，d 为嵌套深度
 */
class NestedInteger {
 public:
  // Constructor initializes an empty nested list.
  NestedInteger();

  // Constructor initializes a single integer.
  NestedInteger(int value);

  // Return true if this NestedInteger holds a single integer.
  bool isInteger() const;

  // Return the single integer that this NestedInteger holds.
  int getInteger() const;

  // Set this NestedInteger to hold a single integer.
  void setInteger(int value);

  // Set this NestedInteger to hold a nested list and adds a nested integer to it.
  void add(const NestedInteger &ni);

  // Return the nested list that this NestedInteger holds.
  const vector<NestedInteger> &getList() const;

 private:
  bool is_integer_;
  int value_;
  vector<NestedInteger> list_;
};

class MiniParserSolution {
 public:
  NestedInteger deserialize(string s);
};

}  // namespace problem_385
}  // namespace leetcode
