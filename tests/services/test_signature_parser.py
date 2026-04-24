#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import unittest

from script.leetcode.exceptions import SignatureError
from script.leetcode.services.signature_parser import SignatureParser
from script.leetcode.services.design_class_extractor import DesignClassExtractor


class TestSignatureParser(unittest.TestCase):
    def test_extract_from_code_template(self) -> None:
        template = """
class Solution {
public:
    int add(int a, int b) { return a + b; }
};
"""
        signature = SignatureParser.extract_from_code_template(template)
        self.assertEqual(signature, "int add(int a, int b)")

    def test_parse_nested_template_params(self) -> None:
        signature = "vector<int> solve(map<int, vector<string>> mp, int k)"
        parsed = SignatureParser.parse(signature)
        self.assertEqual(parsed.return_type, "vector<int>")
        self.assertEqual(parsed.name, "solve")
        self.assertEqual(len(parsed.parameters), 2)
        self.assertEqual(parsed.parameters[0].type, "map<int, vector<string>>")
        self.assertEqual(parsed.parameters[0].name, "mp")
        self.assertEqual(parsed.parameters[1].type, "int")
        self.assertEqual(parsed.parameters[1].name, "k")

    def test_parse_invalid_signature_raises(self) -> None:
        with self.assertRaises(SignatureError):
            SignatureParser.parse("not a valid signature")


class TestDesignClassExtractor(unittest.TestCase):
    def test_extract_design_class_and_methods(self) -> None:
        code = """
class LRUCache {
public:
    LRUCache(int capacity) {}
    int get(int key) { return 0; }
    void put(int key, int value) {}
};
"""
        class_def = DesignClassExtractor.extract(code)
        self.assertIsNotNone(class_def)
        assert class_def is not None
        self.assertEqual(class_def.class_name, "LRUCache")
        self.assertEqual(len(class_def.methods), 3)
        self.assertTrue(class_def.methods[0].is_constructor)

    def test_format_method_declarations(self) -> None:
        code = """
class MyQueue {
public:
    MyQueue() {}
    bool empty() { return true; }
};
"""
        class_def = DesignClassExtractor.extract(code)
        assert class_def is not None
        decls = DesignClassExtractor.format_method_declarations(class_def)
        self.assertIn("MyQueue();", decls)
        self.assertIn("bool empty();", decls)


if __name__ == "__main__":
    unittest.main()
