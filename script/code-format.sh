#!/usr/bin/env bash

# 检查 clang-format 是否安装
if ! command -v clang-format &> /dev/null; then
    echo "错误: clang-format 未安装"
    echo "请安装: sudo apt install clang-format"
    exit 1
fi

# 查找所有需要格式化的文件
files=$(find include/ src/ test/ \
    -type f \( -name '*.c' -o -name '*.cpp' -o -name '*.cc' -o -name '*.h' -o -name '*.hpp' \))

if [ -z "$files" ]; then
    echo "未找到需要格式化的文件"
    exit 0
fi

# 统计文件数量
file_count=$(echo "$files" | wc -l)
echo "找到 $file_count 个文件，开始格式化..."

# 获取项目根目录的绝对路径（确保能找到 .clang-format）
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

# 检查 .clang-format 文件是否存在
if [ ! -f "$PROJECT_ROOT/.clang-format" ]; then
    echo "警告: 未找到 .clang-format 配置文件，将使用默认样式"
fi

# 格式化每个文件并显示进度（每10个文件显示一次）
count=0
echo "$files" | while IFS= read -r file; do
    count=$((count + 1))
    if [ $((count % 10)) -eq 0 ] || [ $count -eq 1 ] || [ $count -eq $file_count ]; then
        echo "[$count/$file_count] 格式化中..."
    fi
    # 使用 -style=file 明确指定从 .clang-format 文件读取配置
    # clang-format 会从文件所在目录向上查找 .clang-format 文件
    clang-format -style=file -i "$file" 2>/dev/null
done

echo ""
echo "✓ 代码格式化完成，共处理 $file_count 个文件"