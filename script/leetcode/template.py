INCLUDE_TEMPLATE = """
#include "leetcode/core.h"

namespace leetcode {{
namespace problem_{problem_id} {{

using Func = std::function<{solution_return_type}({solution_param_type})>;

class {solution_class_name}{solution_class_suffix} : public SolutionBase<Func> {{
 public:
  //! {problem_id}. {problem_title}
  //! {leetcode_url_prefix}{problem_slug}/
  {solution_return_type} {solution_func_name}({solution_param});

  {solution_class_name}{solution_class_suffix}();
}};

}}  // namespace problem_{problem_id}
}}  // namespace leetcode
"""

SOURCE_TEMPLATE = """
#include "leetcode/problems/{problem_slug}.h"

namespace leetcode {{
namespace problem_{problem_id} {{

static {solution_return_type} solution1({solution_param}) {{
  /* Code here */
  return {solution_return_type}();
}}

{solution_class_name}{solution_class_suffix}::{solution_class_name}{solution_class_suffix}() {{
  setMetaInfo({{
      .id = {problem_id},
      .title = "{problem_title}",
      .url = "{leetcode_url_prefix}{problem_slug}"
  }});
  registerStrategy("Brute Force", solution1);
}}

{solution_return_type} {solution_class_name}{solution_class_suffix}::{solution_func_name}({solution_param}) {{
  return getSolution()({solution_param_name});
}}

}}  // namespace problem_{problem_id}
}}  // namespace leetcode
"""


TEST_TEMPLATE = """
#include "leetcode/problems/{problem_slug}.h"

#include "gtest/gtest.h"

namespace leetcode {{
namespace problem_{problem_id} {{

class {solution_class_name}{test_class_suffix} : public ::testing::TestWithParam<string> {{
 protected:
  void SetUp() override {{ solution.setStrategy(GetParam()); }}

  {solution_class_name}{solution_class_suffix} solution;
}};

TEST_P({solution_class_name}{test_class_suffix}, Example1) {{
  /*Add Test Body here */
}}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, {solution_class_name}{test_class_suffix},
    ::testing::ValuesIn({solution_class_name}{solution_class_suffix}().getStrategyNames()));

}}  // namespace problem_{problem_id}
}}  // namespace leetcode
"""

# 设计类题目模板（从代码模板自动生成）
DESIGN_INCLUDE_TEMPLATE = """
#include "leetcode/core.h"

namespace leetcode {{
namespace problem_{problem_id} {{

//! {problem_id}. {problem_title}
//! https://leetcode.com/problems/{problem_slug}/
class {solution_class_name} {{
 public:
{method_declarations}

 private:
  // TODO: 添加私有成员变量和辅助方法
}};

}}  // namespace problem_{problem_id}
}}  // namespace leetcode
"""

DESIGN_SOURCE_TEMPLATE = """
#include "leetcode/problems/{problem_slug}.h"

namespace leetcode {{
namespace problem_{problem_id} {{

{method_implementations}

}}  // namespace problem_{problem_id}
}}  // namespace leetcode
"""

DESIGN_TEST_TEMPLATE = """
#include "leetcode/problems/{problem_slug}.h"

#include "gtest/gtest.h"

namespace leetcode {{
namespace problem_{problem_id} {{

TEST(LeetCode, {solution_class_name}Test) {{
  // TODO: 编写测试用例
  // 参考 LeetCode 的示例编写测试
  // 示例：
  // {solution_class_name} obj;
  // obj.method1();
  // EXPECT_EQ(expected, actual);
}}

}}  // namespace problem_{problem_id}
}}  // namespace leetcode
"""

SOLVED_PROBLEM_DOC_HEADER = """
# 已经解决的 LeetCode 题目

| ID | Title | Solution |
|----|-------|----------|
"""
