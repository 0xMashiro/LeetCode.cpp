#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""@expected 注释解析 + 缩写映射。"""

import unittest

from script.leetcode.submit.expected_verdicts import parse_expected_verdicts, resolve_expected


_SRC_TWO_STRATEGIES = """
namespace x {
void register_all(Solution& s) {
    // @expected: TLE
    s.registerStrategy("BruteForce", [&]{});

    s.registerStrategy("Optimal", [&]{});
}
}
"""

_SRC_FULL_NAMES = """
    // @expected: Wrong Answer
    s.registerStrategy("Broken", [&]{});
    // @expected: Accepted
    s.registerStrategy("Correct", [&]{});
"""

_SRC_NO_ANNOTATIONS = """
    s.registerStrategy("A", [&]{});
    s.registerStrategy("B", [&]{});
"""

_SRC_MIXED = """
    s.registerStrategy("A", [&]{});
    // @expected: TLE
    s.registerStrategy("B", [&]{});
    s.registerStrategy("C", [&]{});
"""


class TestParseExpectedVerdicts(unittest.TestCase):
    def test_shorthand_maps_to_leetcode_status(self) -> None:
        self.assertEqual(
            parse_expected_verdicts(_SRC_TWO_STRATEGIES),
            {1: "Time Limit Exceeded"},
        )

    def test_full_name_also_accepted(self) -> None:
        out = parse_expected_verdicts(_SRC_FULL_NAMES)
        self.assertEqual(out, {1: "Wrong Answer", 2: "Accepted"})

    def test_no_annotations_returns_empty(self) -> None:
        self.assertEqual(parse_expected_verdicts(_SRC_NO_ANNOTATIONS), {})

    def test_partial_annotations_keep_indexes(self) -> None:
        """只给 B 加了注释 → 只返回 B 的条目，A 和 C 走默认。"""
        self.assertEqual(parse_expected_verdicts(_SRC_MIXED), {2: "Time Limit Exceeded"})

    def test_unknown_alias_is_ignored(self) -> None:
        src = """
        // @expected: Banana
        s.registerStrategy("X", [&]{});
        """
        self.assertEqual(parse_expected_verdicts(src), {})

    def test_trailing_comment_same_line(self) -> None:
        """行尾注释也应该绑到同一条 registerStrategy。"""
        src = """
        s.registerStrategy("BruteForce", [&]{});  // @expected: TLE
        s.registerStrategy("Optimal", [&]{});
        """
        self.assertEqual(parse_expected_verdicts(src), {1: "Time Limit Exceeded"})

    def test_mixed_leading_and_trailing(self) -> None:
        src = """
        // @expected: TLE
        s.registerStrategy("A", [&]{});
        s.registerStrategy("B", [&]{});  // @expected: WA
        s.registerStrategy("C", [&]{});
        """
        self.assertEqual(
            parse_expected_verdicts(src),
            {1: "Time Limit Exceeded", 2: "Wrong Answer"},
        )


class TestResolveExpected(unittest.TestCase):
    def test_default_accepted(self) -> None:
        self.assertEqual(resolve_expected({}, 1), "Accepted")

    def test_explicit_override(self) -> None:
        self.assertEqual(
            resolve_expected({1: "Time Limit Exceeded"}, 1),
            "Time Limit Exceeded",
        )


if __name__ == "__main__":
    unittest.main()
