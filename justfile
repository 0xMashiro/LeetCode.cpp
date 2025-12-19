# LeetCode C++ 项目命令工具

set windows-powershell := true

# Use python on Windows, python3 on Unix-like systems
python := if os_family() == "windows" { "python" } else { "python3" }

# 默认命令：显示帮助
default:
    @echo "LeetCode.cpp 项目命令："
    @echo ""
    @echo "构建："
    @echo "  just build          - 构建项目（Debug）"
    @echo "  just build-release  - 构建项目（Release）"
    @echo "  just clean          - 清理构建文件"
    @echo "  just rebuild        - 清理并重新构建"
    @echo ""
    @echo "测试："
    @echo "  just test           - 运行所有测试"
    @echo "  just test <ID>      - 运行指定题目测试"
    @echo "  just test-filter <FILTER> - 运行过滤后的测试"
    @echo ""
    @echo "题目管理："
    @echo "  just add <ID> [--force]  - 添加题目（--force 强制覆盖）"
    @echo "  just rm <ID>             - 删除题目"
    @echo "  just doc                 - 生成已解决题目文档"
    @echo "  just leetcode <ARGS>     - LeetCode CLI 通用命令"
    @echo ""
    @echo "代码格式化："
    @echo "  just format              - 格式化所有代码"

# LeetCode 题目管理
leetcode +ARGS:
    {{python}} script/leetcode/cli.py {{ARGS}}

# 简化的题目管理命令
add TARGET *ARGS:
    {{python}} script/leetcode/cli.py add {{TARGET}} {{ARGS}}

rm TARGET:
    {{python}} script/leetcode/cli.py rm {{TARGET}}

doc:
    {{python}} script/leetcode/cli.py doc

# 构建项目
build:
    @mkdir -p build
    cd build && cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Debug && cmake --build . -j

build-release:
    @mkdir -p build
    cd build && cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release && cmake --build . -j

clean:
    rm -rf build

rebuild:
    just clean
    just build

# 运行测试
test ID="":
    @if [ ! -f build/bin/problem_set_tests ]; then \
        echo "请先构建项目: just build"; \
        exit 1; \
    fi
    @if [ -z "{{ID}}" ]; then \
        ./build/bin/problem_set_tests; \
    else \
        {{python}} script/leetcode/cli.py test {{ID}}; \
    fi

test-filter FILTER:
    @if [ ! -f build/bin/problem_set_tests ]; then \
        echo "请先构建项目: just build"; \
        exit 1; \
    fi
    ./build/bin/problem_set_tests --gtest_filter={{FILTER}}

# 代码格式化
format:
    @bash script/code-format.sh
