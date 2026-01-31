#!/usr/bin/env python3
"""
CI helper script: Detect changed problem files

Usage:
    python detect_changed_problems.py [base_ref]

Args:
    base_ref: Base branch or commit to compare, defaults to origin/main

Output:
    Semicolon-separated list of problem slugs, suitable for CMake
"""

import subprocess
import sys
import re
from pathlib import Path


def get_changed_files(base_ref: str) -> list:
    """Get list of changed files"""
    try:
        result = subprocess.run(
            ["git", "diff", "--name-only", base_ref, "HEAD"],
            capture_output=True,
            text=True,
            check=True,
        )
        return result.stdout.strip().split("\n") if result.stdout.strip() else []
    except subprocess.CalledProcessError as e:
        print(f"Error getting changed files: {e}", file=sys.stderr)
        sys.exit(1)


def get_all_files_in_commit() -> list:
    """Get all files in current commit (for CI push events)"""
    try:
        result = subprocess.run(
            ["git", "diff-tree", "--no-commit-id", "--name-only", "-r", "HEAD"],
            capture_output=True,
            text=True,
            check=True,
        )
        return result.stdout.strip().split("\n") if result.stdout.strip() else []
    except subprocess.CalledProcessError as e:
        print(f"Error getting commit files: {e}", file=sys.stderr)
        sys.exit(1)


def extract_problem_slug(file_path: str) -> str:
    """Extract problem slug from file path"""
    patterns = [
        r"src/leetcode/problems/([\w-]+)\.cpp$",
        r"include/leetcode/problems/([\w-]+)\.h$",
        r"test/leetcode/problems/([\w-]+)\.cpp$",
    ]
    
    for pattern in patterns:
        match = re.search(pattern, file_path)
        if match:
            return match.group(1)
    return None


def detect_changed_problems(base_ref: str = "origin/main") -> set:
    """Detect changed problems"""
    changed_files = get_changed_files(base_ref)
    
    # If no changes, might be CI push event, try getting current commit files
    if not changed_files or changed_files == [""]:
        changed_files = get_all_files_in_commit()
    
    problems = set()
    for file_path in changed_files:
        slug = extract_problem_slug(file_path)
        if slug:
            # Verify all three files exist (ensure complete problem)
            src_file = Path(f"src/leetcode/problems/{slug}.cpp")
            hdr_file = Path(f"include/leetcode/problems/{slug}.h")
            test_file = Path(f"test/leetcode/problems/{slug}.cpp")
            
            if src_file.exists() and hdr_file.exists() and test_file.exists():
                problems.add(slug)
            else:
                print(f"Warning: {slug} has incomplete files, skipping", file=sys.stderr)
    
    return problems


def main():
    base_ref = sys.argv[1] if len(sys.argv) > 1 else "origin/main"
    
    problems = detect_changed_problems(base_ref)
    
    if not problems:
        print("No changed problems detected", file=sys.stderr)
        print("")  # Output empty string
        sys.exit(0)
    
    # Output semicolon-separated list
    output = ";".join(sorted(problems))
    print(output)
    
    # Also output to stderr for debugging
    print(f"Detected {len(problems)} changed problem(s): {output}", file=sys.stderr)


if __name__ == "__main__":
    main()
