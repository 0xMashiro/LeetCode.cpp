#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
模板渲染器
"""

from typing import Dict, Any

# 普通题目模板
INCLUDE_TEMPLATE = """#include "leetcode/core.h"

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

SOURCE_TEMPLATE = """#include "leetcode/problems/{problem_slug}.h"

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

TEST_TEMPLATE = """#include "leetcode/problems/{problem_slug}.h"

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

# 设计类题目模板
DESIGN_INCLUDE_TEMPLATE = """#include "leetcode/core.h"

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

DESIGN_SOURCE_TEMPLATE = """#include "leetcode/problems/{problem_slug}.h"

namespace leetcode {{
namespace problem_{problem_id} {{

{method_implementations}

}}  // namespace problem_{problem_id}
}}  // namespace leetcode
"""

DESIGN_TEST_TEMPLATE = """#include "leetcode/problems/{problem_slug}.h"

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

# 已解决题目文档头部
SOLVED_PROBLEM_DOC_HEADER = """# 已经解决的 LeetCode 题目

| ID | Title | Solution |
|----|-------|----------|
"""


class TemplateRenderer:
    """模板渲染器"""
    
    # 模板映射
    TEMPLATES = {
        'header': {
            'ordinary': INCLUDE_TEMPLATE,
            'design': DESIGN_INCLUDE_TEMPLATE,
        },
        'source': {
            'ordinary': SOURCE_TEMPLATE,
            'design': DESIGN_SOURCE_TEMPLATE,
        },
        'test': {
            'ordinary': TEST_TEMPLATE,
            'design': DESIGN_TEST_TEMPLATE,
        },
    }
    
    @classmethod
    def render(
        cls, 
        template_type: str, 
        is_design: bool = False, 
        **context: Any
    ) -> str:
        """渲染模板
        
        Args:
            template_type: 模板类型 ('header', 'source', 'test')
            is_design: 是否是设计类题目
            **context: 模板变量
        
        Returns:
            渲染后的模板字符串
        """
        template_key = 'design' if is_design else 'ordinary'
        template = cls.TEMPLATES[template_type][template_key]
        return template.format(**context)
    
    @classmethod
    def render_ordinary_header(cls, **context) -> str:
        """渲染普通题目头文件"""
        return cls.render('header', False, **context)
    
    @classmethod
    def render_ordinary_source(cls, **context) -> str:
        """渲染普通题目源文件"""
        return cls.render('source', False, **context)
    
    @classmethod
    def render_ordinary_test(cls, **context) -> str:
        """渲染普通题目测试文件"""
        return cls.render('test', False, **context)
    
    @classmethod
    def render_design_header(cls, **context) -> str:
        """渲染设计类题目头文件"""
        return cls.render('header', True, **context)
    
    @classmethod
    def render_design_source(cls, **context) -> str:
        """渲染设计类题目源文件"""
        return cls.render('source', True, **context)
    
    @classmethod
    def render_design_test(cls, **context) -> str:
        """渲染设计类题目测试文件"""
        return cls.render('test', True, **context)
