#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import unittest
import urllib.error
from email.message import Message
from io import BytesIO
from unittest.mock import patch

from script.leetcode import cookie as leetcode_cookie
from script.leetcode.submit import http_api


class FakeResponse:
    def __init__(self, headers: Message):
        self.headers = headers

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc, tb):
        return False


class TestCookiePreparation(unittest.TestCase):
    def test_normalize_cookie_header_drops_set_cookie_attributes(self) -> None:
        cookie = (
            "LEETCODE_SESSION=abc; Domain=.leetcode.com; expires=Fri, 26 Jun 2026 "
            "05:17:59 GMT; HttpOnly; Max-Age=1209600; Path=/; SameSite=Lax; Secure"
        )

        self.assertEqual(leetcode_cookie.normalize_cookie_header(cookie), "LEETCODE_SESSION=abc")

    @patch("urllib.request.urlopen")
    def test_prepare_cookie_fetches_missing_csrf_token(self, mock_urlopen) -> None:
        headers = Message()
        headers.add_header("Set-Cookie", "csrftoken=csrf123; expires=Fri, 26 Jun 2026 05:17:59 GMT; Path=/")
        mock_urlopen.return_value = FakeResponse(headers)

        cookie, csrf = leetcode_cookie.prepare_cookie("LEETCODE_SESSION=abc")

        self.assertEqual(csrf, "csrf123")
        self.assertEqual(cookie, "csrftoken=csrf123; LEETCODE_SESSION=abc")

    @patch("urllib.request.urlopen")
    def test_prepare_cookie_uses_existing_csrf_token_when_refresh_fails(self, mock_urlopen) -> None:
        mock_urlopen.side_effect = OSError("offline")

        cookie, csrf = leetcode_cookie.prepare_cookie("csrftoken=old; LEETCODE_SESSION=abc")

        self.assertEqual(csrf, "old")
        self.assertEqual(cookie, "csrftoken=old; LEETCODE_SESSION=abc")

    @patch("urllib.request.urlopen")
    def test_prepare_cookie_refreshes_existing_csrf_token(self, mock_urlopen) -> None:
        headers = Message()
        headers.add_header("Set-Cookie", "csrftoken=new; Path=/")
        mock_urlopen.return_value = FakeResponse(headers)

        cookie, csrf = leetcode_cookie.prepare_cookie("csrftoken=old; LEETCODE_SESSION=abc")

        self.assertEqual(csrf, "new")
        self.assertEqual(cookie, "csrftoken=new; LEETCODE_SESSION=abc")


class TestLeetCodeHttpClient(unittest.TestCase):
    @patch("urllib.request.urlopen")
    def test_submit_preserves_http_error_type(self, mock_urlopen) -> None:
        mock_urlopen.side_effect = urllib.error.HTTPError(
            url="https://leetcode.com/problems/two-sum/submit/",
            code=499,
            msg="client closed request",
            hdrs=None,
            fp=BytesIO(b"csrf rejected"),
        )

        client = http_api.LeetCodeHttpClient("csrftoken=c; LEETCODE_SESSION=s", "c")
        result = client.submit("two-sum", "1", "class Solution {};")

        self.assertEqual(result.status, "Error")
        self.assertEqual(result.status_code, 499)
        self.assertEqual(result.error_type, "http_499")
        self.assertIn("csrf rejected", result.error_message or "")

    @patch("urllib.request.urlopen")
    def test_submit_missing_submission_id_is_typed(self, mock_urlopen) -> None:
        headers = Message()
        mock_urlopen.return_value = FakeJsonResponse({"error": "bad request"}, headers)

        client = http_api.LeetCodeHttpClient("csrftoken=c; LEETCODE_SESSION=s", "c")
        result = client.submit("two-sum", "1", "class Solution {};")

        self.assertEqual(result.status, "Error")
        self.assertEqual(result.error_type, "submit_response_missing_id")


class FakeJsonResponse(FakeResponse):
    def __init__(self, payload: dict, headers: Message):
        super().__init__(headers)
        self._payload = payload

    def read(self) -> bytes:
        import json

        return json.dumps(self._payload).encode("utf-8")


if __name__ == "__main__":
    unittest.main()
