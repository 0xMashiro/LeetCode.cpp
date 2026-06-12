#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import unittest
from unittest.mock import MagicMock, patch

from script.leetcode.submit.submitter import LeetCodeSubmitter


class TestLeetCodeSubmitterInit(unittest.TestCase):
    def test_init_uses_cookie_prepare_helper(self) -> None:
        prepare = MagicMock(return_value=("csrftoken=c; LEETCODE_SESSION=s", "c"))
        with patch.dict(os.environ, {"LEETCODE_COOKIE": "raw-cookie"}, clear=True):
            with patch("script.leetcode.submit.submitter.load_dotenv", return_value=None):
                with patch("script.leetcode.submit.submitter.ProblemRepository"):
                    with patch.object(LeetCodeSubmitter, "_init_ai_client", return_value=None):
                        with patch.dict(
                            LeetCodeSubmitter.__init__.__globals__,
                            {"prepare_cookie": prepare},
                        ):
                            with patch(
                                "script.leetcode.submit.submitter.http_api.validate_cookie",
                                return_value=True,
                            ):
                                with patch("script.leetcode.submit.submitter.LeetCodeHttpClient"):
                                    submitter = LeetCodeSubmitter()

        prepare.assert_called_once_with("raw-cookie")
        self.assertEqual(submitter.cookie, "csrftoken=c; LEETCODE_SESSION=s")
        self.assertEqual(submitter.csrf_token, "c")


if __name__ == "__main__":
    unittest.main()
