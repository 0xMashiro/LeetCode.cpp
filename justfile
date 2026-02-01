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
    @echo "  just build          - 构建项目（Debug，全量）"
    @echo "  just build-release  - 构建项目（Release，全量）"
    @echo "  just single <ID>    - 只构建单个题目（快速）"
    @echo "  just multi <IDs...> - 构建多个题目（CI 优化）"
    @echo "  just clean          - 清理构建文件"
    @echo "  just rebuild        - 清理并重新构建"
    @echo ""
    @echo "测试："
    @echo "  just test           - 运行所有测试"
    @echo "  just test <ID>      - 运行指定题目测试（需先全量构建）"
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
    @echo "  just ai-solve --report   - 生成解题报告（CI 使用）"
    @echo "  just ai-solve --random   - 随机挑选未解决的题目（测试用）"
    @echo "  just ai-solve --auto     - 自动循环解决所有未完成的题目"
    @echo ""
    @echo "LeetCode 提交："
    @echo "  just submit <ID>         - 转换并提交到 LeetCode（默认第1个解法）"
    @echo "  just submit <ID> -n 2  - 提交第2个解法到 LeetCode"
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
    cd build && cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Debug -DLEETCODE_SINGLE_PROBLEM="" && cmake --build . -j

build-release:
    @mkdir -p build
    cd build && cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release -DLEETCODE_SINGLE_PROBLEM="" && cmake --build . -j

clean:
    rm -rf build

rebuild:
    just clean
    just build

# 单题编译运行（快速，只编译指定题目）
single ID:
    #!/usr/bin/env bash
    set -e
    unset LD_LIBRARY_PATH
    
    ID="{{ID}}"
    if [ -z "$ID" ]; then
        echo "用法: just single <ID>"
        echo "示例: just single 1"
        exit 1
    fi
    
    echo "正在解析题目..."
    SLUG=$({{python_venv}} script/leetcode/get_slug.py "$ID")
    echo "  $ID -> $SLUG"
    
    echo ""
    echo "开始编译单题..."
    mkdir -p build
    cd build
    cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Debug -DLEETCODE_SINGLE_PROBLEM="$SLUG"
    cmake --build . -j
    echo ""
    echo "运行测试..."
    ./bin/single_problem_test

# 多题编译运行（编译指定题目列表，适合 CI）
# 示例: just multi 1 2 146 lru-cache
multi *IDS:
    #!/usr/bin/env bash
    set -e
    unset LD_LIBRARY_PATH
    
    IDS="{{IDS}}"
    if [ -z "$IDS" ]; then
        echo "用法: just multi <ID1> [ID2] [ID3] ..."
        echo "示例: just multi 1 2 146"
        exit 1
    fi
    
    echo "正在解析题目列表..."
    SLUGS=""
    COUNT=0
    for ID in $IDS; do
        SLUG=$({{python_venv}} script/leetcode/get_slug.py "$ID")
        if [ -n "$SLUGS" ]; then
            SLUGS="$SLUGS;$SLUG"
        else
            SLUGS="$SLUG"
        fi
        echo "  $ID -> $SLUG"
        COUNT=$((COUNT + 1))
    done
    
    echo ""
    echo "共 $COUNT 个题目，开始编译..."
    mkdir -p build
    cd build
    cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Debug -DLEETCODE_MULTI_PROBLEMS="$SLUGS"
    cmake --build . -j
    echo ""
    echo "运行测试..."
    ./bin/multi_problem_test

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

# 提交到 LeetCode
submit ID *ARGS:
    {{python_venv}} -m script.leetcode.submit {{ID}} {{ARGS}}

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
