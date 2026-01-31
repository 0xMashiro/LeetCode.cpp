# LeetCode C++ 项目命令工具

set windows-powershell := true

# Use python on Windows, python3 on Unix-like systems
python := if os_family() == "windows" { "python" } else { "python3" }

# Python virtual environment
# 如果存在 venv，使用 venv 中的 python，否则使用系统 python
# 使用 shell 命令检查文件是否存在
python_venv := `test -f venv/bin/python && echo "venv/bin/python" || echo "{{python}}"`

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
    @echo ""
    @echo "AI 自动解题："
    @echo "  just ai-solve            - 使用 AI 解决每日一题"
    @echo "  just ai-solve <ID>       - 使用 AI 解决指定题目"
    @echo ""
    @echo "Python 环境："
    @echo "  just venv-setup          - 创建并设置虚拟环境"
    @echo "  just venv-install        - 安装 Python 依赖"

# LeetCode 题目管理
leetcode +ARGS:
    {{python_venv}} -m script.leetcode.cli {{ARGS}}

# 简化的题目管理命令
add TARGET *ARGS:
    {{python_venv}} -m script.leetcode.cli add {{TARGET}} {{ARGS}}

rm TARGET:
    {{python_venv}} -m script.leetcode.cli rm {{TARGET}}

doc:
    {{python_venv}} -m script.leetcode.cli doc

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
        {{python_venv}} -m script.leetcode.cli test {{ID}}; \
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

# AI 自动解题
ai-solve *ARGS:
    {{python_venv}} -m script.leetcode.ai.solver {{ARGS}}

# Python 虚拟环境管理
venv-setup:
    @if [ -d "venv" ]; then \
        echo "虚拟环境已存在"; \
    else \
        echo "创建虚拟环境..."; \
        {{python}} -m venv venv; \
        echo "✓ 虚拟环境已创建"; \
        echo ""; \
        echo "激活虚拟环境:"; \
        echo "  source venv/bin/activate"; \
        echo ""; \
        echo "或使用 just venv-install 自动安装依赖"; \
    fi

venv-install:
    @if [ ! -d "venv" ]; then \
        echo "虚拟环境不存在，正在创建..."; \
        {{python}} -m venv venv; \
    fi
    @echo "安装 Python 依赖..."
    venv/bin/pip install --upgrade pip
    venv/bin/pip install -r requirements.txt
    @echo "✓ 依赖安装完成"
