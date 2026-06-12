#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
把 AI_SOLVER_METRICS_DIR 下的 metrics_*.json 汇总为 CSV，并打印均值 / 标准差对比。

用法：
    python -m script.leetcode.ai.aggregate_metrics <metrics_dir>
    python -m script.leetcode.ai.aggregate_metrics <metrics_dir> --csv summary.csv
"""

import argparse
import csv
import json
import statistics
import sys
from pathlib import Path
from typing import Any, Dict, Iterable, List

FIELDS = [
    "problem_id",
    "provider",
    "model",
    "thinking_enabled",
    "rounds",
    "api_calls",
    "total_api_time",
    "total_solve_time",
    "success",
    "leetcode_passed",
    "skip_reason",
    "failure_reason",
    "prompt_tokens",
    "completion_tokens",
    "total_tokens",
]


def load_metrics(metrics_dir: Path) -> List[Dict[str, Any]]:
    """加载目录下所有 metrics_*.json"""
    records = []
    for path in sorted(metrics_dir.glob("metrics_*.json")):
        try:
            records.append(json.loads(path.read_text(encoding="utf-8")))
        except Exception as e:  # noqa: BLE001
            print(f"跳过无法解析的文件 {path}: {e}", file=sys.stderr)
    return records


def write_csv(records: Iterable[Dict[str, Any]], out_path: Path) -> None:
    """按 FIELDS 顺序落 CSV"""
    out_path.parent.mkdir(parents=True, exist_ok=True)
    with out_path.open("w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(f, fieldnames=FIELDS)
        writer.writeheader()
        for record in records:
            writer.writerow({key: record.get(key, "") for key in FIELDS})


def _config_key(record: Dict[str, Any]) -> str:
    think = "on" if record.get("thinking_enabled") else "off"
    return f"{record.get('provider')}/{record.get('model')}/think-{think}"


def print_summary(records: List[Dict[str, Any]]) -> None:
    """按 (provider, model, thinking) 分组打印成功率 / 耗时 / 轮数均值"""
    if not records:
        print("(no metrics)")
        return

    groups: Dict[str, List[Dict[str, Any]]] = {}
    for record in records:
        groups.setdefault(_config_key(record), []).append(record)

    header = (
        f"{'配置':<45} {'n':>3} {'成功率':>7} {'轮次均值':>10} "
        f"{'API耗时均值':>14} {'总耗时均值':>12} {'Token均值':>12}"
    )
    print(header)
    print("-" * len(header))
    for key in sorted(groups):
        rows = groups[key]
        n = len(rows)
        success_rate = sum(1 for r in rows if r.get("success")) / n
        rounds_mean = statistics.mean(r.get("rounds", 0) for r in rows)
        api_time_mean = statistics.mean(r.get("total_api_time", 0.0) for r in rows)
        solve_time_mean = statistics.mean(r.get("total_solve_time", 0.0) for r in rows)
        # total_tokens 老 metrics 里没有 → 用 0 占位，均值不偏
        token_mean = statistics.mean(r.get("total_tokens", 0) or 0 for r in rows)
        token_col = f"{token_mean:,.0f}" if token_mean > 0 else "-"
        print(
            f"{key:<45} {n:>3} {success_rate:>7.1%} {rounds_mean:>10.2f} "
            f"{api_time_mean:>12.1f}s {solve_time_mean:>10.1f}s {token_col:>12}"
        )


def main() -> int:
    parser = argparse.ArgumentParser(description="汇总实验指标 JSON → CSV")
    parser.add_argument("metrics_dir", help="包含 metrics_*.json 的目录")
    parser.add_argument("--csv", help="输出 CSV 路径（可选，默认仅打印摘要）")
    args = parser.parse_args()

    metrics_dir = Path(args.metrics_dir)
    if not metrics_dir.is_dir():
        print(f"目录不存在: {metrics_dir}", file=sys.stderr)
        return 1

    records = load_metrics(metrics_dir)
    print(f"已加载 {len(records)} 条指标\n")

    print_summary(records)

    if args.csv:
        out_path = Path(args.csv)
        write_csv(records, out_path)
        print(f"\nCSV 已写入: {out_path}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
