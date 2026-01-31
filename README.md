# LeetCode.cpp

这是很久之前我的 LeetCode C++ 刷题项目，里面有很多懒人功能，现在整理一下方便计算机新生刷题使用，旧的题解已经被清空。
后续佛系更新，你可以查看 [已经解决的 LeetCode 题目](./SOLVED.md) ，代码注释可能会比较少，你可以使用 AI 辅助理解。
By the way, 在 Vibe Coding 时代还有人需要刷算法题吗？🤨 好像架构和设计变得越来越重要了。

我尽可能把这个项目变成一个现代化工程（真的能跑起来！不是代码集！），目前已经可以依赖 AI 大模型驱动自动更新题解，详情参考
[ai-generated](https://github.com/0xMashiro/LeetCode.cpp/pulls?q=label%3Aai-generated) 标签
与 [daily-challenge](./.github/workflows/daily-challenge.yml) 工作流。

真的越来越懒惰了 Orz

## ✨ 特性

- 🎯 **一题多解**：使用策略模式实现多种解法，便于对比学习
- 🧪 **自动化测试**：Google Test 参数化测试，自动覆盖所有解法
- 🤖 **代码生成**：Python 脚本自动生成题目模板，减少重复工作
- 🔧 **工具链完善**：统一使用 `just` 管理所有命令，懒到极致
- 🚀 **CI/CD**：GitHub Actions 自动构建和测试
- 📝 **代码规范**：自动检查和修复代码规范问题

你也可以补充你的题解，并提交 PR 到这个项目，最好保持一致的代码风格：

- 禁止 C 风格代码，提倡使用现代 C++ 语法
- 能使用 STL 容器的话就不要自己实现，不要手搓原始数据结构
- 不追求极致的性能，但也要保证时间复杂度和空间复杂度符合要求

## 📋 环境要求

- **操作系统**：Ubuntu/Linux（Windows 用户请使用 [WSL](https://learn.microsoft.com/zh-cn/windows/wsl/install)）
- **编译器**：GCC（支持 C++20）
- **构建工具**：CMake 3.16+

## 🚀 快速开始

### 安装系统依赖

```bash
sudo apt update
sudo apt install cmake build-essential ccache ninja-build just python3
```

### 构建和测试

```bash
just build      # 构建项目（Debug）
just test       # 运行所有测试
```

输入 `just` 查看所有可用命令。

## 📖 使用指南

### 添加新题目

```bash
just add <ID>    # 添加题目
```

脚本会自动生成：

- 头文件（`include/leetcode/problems/xxx.h`）
- 实现文件（`src/leetcode/problems/xxx.cpp`）
- 测试文件（`test/leetcode/problems/xxx.cpp`）

只需要去修改实现文件和测试文件，头文件通常不需要修改。

### 实现多种解法

一定要记得在实现文件中注册所有策略，并且提供策略名称：

```cpp
TwoSumSolution::TwoSumSolution() {
  registerStrategy("Brute Force", solution1);
  registerStrategy("Hash Table", solution2);
  // 更多解法...
}
```

如果你实现了多种解法，却忘记了注册相应的策略，那么就无法得到完整的测试覆盖。

参考示例：

- [Two Sum](src/leetcode/problems/two-sum.cpp) - 普通题目的多解法实现示例
- [LRU Cache](src/leetcode/problems/lru-cache.cpp) - 设计类题目的实现示例

测试会自动覆盖所有已被注册的解法策略，但是需要你自己添加多个测试用例。

参考示例：

- [Two Sum](test/leetcode/problems/two-sum.cpp) - 普通题目的多解法测试示例
- [LRU Cache](test/leetcode/problems/lru-cache.cpp) - 设计类题目的测试示例

建议先查看这两个示例了解项目的代码风格和实现模式。

### 运行测试

```bash
just test                 # 运行所有测试
just test <ID>            # 运行指定题目测试（如：just test 1）
just test-filter <FILTER> # 运行过滤后的测试
```

### 调试代码

推荐通过 VSC 的 C++ TestMate 插件面板进行调试。

## 📄 许可证

本项目采用 Apache License 2.0 许可证，详见 [LICENSE](LICENSE) 文件。
