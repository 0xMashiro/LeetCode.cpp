#!/bin/bash
# 本地模拟 CI 流程

set -e

echo "=== Local CI Simulation ==="

# 1. 模拟检测变更
echo "[Step 1] Detecting changed problems..."
python3 script/ci/detect_changed_problems.py origin/main

# 2. 设置构建参数
PROBLEMS=$(python3 script/ci/detect_changed_problems.py origin/main)

if [ -z "$PROBLEMS" ]; then
    echo "No problems changed, running full build..."
    BUILD_TYPE="full"
else
    echo "Changed problems: $PROBLEMS"
    BUILD_TYPE="incremental"
fi

# 3. 模拟构建
echo "[Step 2] Building ($BUILD_TYPE)..."
mkdir -p build && cd build

if [ "$BUILD_TYPE" == "incremental" ]; then
    cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release -DLEETCODE_MULTI_PROBLEMS="$PROBLEMS"
else
    cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release
fi

cmake --build . -j

# 4. 运行测试
echo "[Step 3] Running tests..."
if [ "$BUILD_TYPE" == "incremental" ]; then
    ./bin/multi_problem_test
else
    ctest --output-on-failure
fi

echo "=== CI Simulation Complete ==="
