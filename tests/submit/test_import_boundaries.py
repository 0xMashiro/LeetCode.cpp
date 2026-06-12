#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import importlib
import sys


def test_submit_package_import_does_not_eagerly_import_submitter() -> None:
    sys.modules.pop("script.leetcode.submit", None)
    sys.modules.pop("script.leetcode.submit.submitter", None)

    package = importlib.import_module("script.leetcode.submit")

    assert "script.leetcode.submit.submitter" not in sys.modules
    assert package.SubmissionResult.__name__ == "SubmissionResult"


def test_submitter_is_not_exported_from_package_root() -> None:
    sys.modules.pop("script.leetcode.submit", None)
    sys.modules.pop("script.leetcode.submit.submitter", None)

    package = importlib.import_module("script.leetcode.submit")

    assert "LeetCodeSubmitter" not in package.__all__
    assert not hasattr(package, "LeetCodeSubmitter")
    assert "script.leetcode.submit.submitter" not in sys.modules
