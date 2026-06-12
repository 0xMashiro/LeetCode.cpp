#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""结构化 strategy expected 解析 + 缩写映射。"""

import unittest

from script.leetcode.submit.expected_verdicts import parse_expected_verdicts, resolve_expected

_SRC_TWO_STRATEGIES = """
namespace x {
void register_all(Solution& s) {
    s.registerStrategy({.name = "BruteForce",
                        .expected = "TLE"},
                       [&]{});

    s.registerStrategy({.name = "Optimal"}, [&]{});
}
}
"""

_SRC_FULL_NAMES = """
    s.registerStrategy({.name = "Broken",
                        .expected = "Wrong Answer"},
                       [&]{});
    s.registerStrategy({.name = "Correct",
                        .expected = "Accepted"},
                       [&]{});
"""

_SRC_NO_ANNOTATIONS = """
    s.registerStrategy({.name = "A"}, [&]{});
    s.registerStrategy({.name = "B"}, [&]{});
"""

_SRC_MIXED = """
    s.registerStrategy({.name = "A"}, [&]{});
    s.registerStrategy({.name = "B",
                        .expected = "TLE"},
                       [&]{});
    s.registerStrategy({.name = "C"}, [&]{});
"""

_SRC_METADATA = """
    s.registerStrategy({.name = "Brute Force",
                        .expected = "Time Limit Exceeded",
                        .time_complexity = "O(nq)"},
                       solution1);
    s.registerStrategy({.name = "Optimal",
                        .expected = "Accepted"},
                       solution2);
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

    def test_no_expected_returns_empty(self) -> None:
        self.assertEqual(parse_expected_verdicts(_SRC_NO_ANNOTATIONS), {})

    def test_partial_expected_keep_indexes(self) -> None:
        """只给 B 加了 expected → 只返回 B 的条目，A 和 C 走默认。"""
        self.assertEqual(parse_expected_verdicts(_SRC_MIXED), {2: "Time Limit Exceeded"})

    def test_unknown_alias_is_ignored(self) -> None:
        src = """
        s.registerStrategy({.name = "X",
                            .expected = "Banana"},
                           [&]{});
        """
        self.assertEqual(parse_expected_verdicts(src), {})

    def test_strategy_metadata_expected_field(self) -> None:
        self.assertEqual(
            parse_expected_verdicts(_SRC_METADATA),
            {1: "Time Limit Exceeded", 2: "Accepted"},
        )

    def test_strategy_metadata_expected_field_can_be_shorthand(self) -> None:
        src = """
        s.registerStrategy({.name = "A",
                            .expected = "AC"},
                           solution1);
        """
        self.assertEqual(parse_expected_verdicts(src), {1: "Accepted"})


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
