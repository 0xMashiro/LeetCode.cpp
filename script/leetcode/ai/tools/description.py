#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
LeetCode 题面 HTML 解析。

原始 ``fetch_problem_metadata`` 里的 ``content`` 字段是原始 HTML（含 <p>/<pre>/<code>/<strong> 等），
flash + 非思考模式解析这个嵌在大 JSON 里的 HTML 很不稳定 —— 它容易认为"已拿到"但事实上没抽出示例，
然后脑补测试值。这里做两件事：

  * ``html_to_markdown`` 把 HTML 压平成 Markdown，去掉 &nbsp; 之类实体。
  * ``extract_examples`` 扫描 "Example N:" 区块，拆出结构化 {index, input, output, explanation}。

二者都不依赖第三方库（只用 stdlib 的 html.parser + re）。解析失败一律降级为原字符串 / 空列表，
任何情况下都不应让主流程抛异常。
"""

import re
from html.parser import HTMLParser
from typing import Dict, List

_HTML_ENTITIES = {
    "&nbsp;": " ",
    "&amp;": "&",
    "&lt;": "<",
    "&gt;": ">",
    "&quot;": '"',
    "&#39;": "'",
    "&apos;": "'",
}


def _decode_entities(text: str) -> str:
    for entity, replacement in _HTML_ENTITIES.items():
        text = text.replace(entity, replacement)
    return text


class _LeetcodeToMarkdown(HTMLParser):
    """把 LeetCode 题面 HTML 压平成 Markdown。只处理实际出现过的 tag 集合。"""

    # 行内样式 → Markdown 包裹符
    _INLINE_WRAPS = {
        "code": "`",
        "em": "*",
        "i": "*",
        "strong": "**",
        "b": "**",
        "sup": "^",
        "sub": "_",
    }

    def __init__(self) -> None:
        super().__init__()
        self._parts: List[str] = []
        self._list_stack: List[str] = []
        self._ol_counter: List[int] = []
        self._in_pre = 0  # 支持嵌套 <pre>；>0 表示在代码块里

    # --- tag handlers ---------------------------------------------------

    def handle_starttag(self, tag: str, attrs) -> None:
        tag = tag.lower()
        if tag == "pre":
            self._in_pre += 1
            self._parts.append("\n```\n")
        elif tag == "br":
            self._parts.append("\n")
        elif tag == "p":
            self._parts.append("\n\n")
        elif tag in ("ul", "ol"):
            self._list_stack.append(tag)
            if tag == "ol":
                self._ol_counter.append(0)
            self._parts.append("\n")
        elif tag == "li":
            kind = self._list_stack[-1] if self._list_stack else "ul"
            if kind == "ol" and self._ol_counter:
                self._ol_counter[-1] += 1
                self._parts.append(f"\n{self._ol_counter[-1]}. ")
            else:
                self._parts.append("\n- ")
        elif tag in self._INLINE_WRAPS:
            self._parts.append(self._INLINE_WRAPS[tag])

    def handle_endtag(self, tag: str) -> None:
        tag = tag.lower()
        if tag == "pre":
            self._in_pre = max(0, self._in_pre - 1)
            self._parts.append("\n```\n")
        elif tag == "p":
            self._parts.append("\n")
        elif tag in ("ul", "ol"):
            if self._list_stack:
                self._list_stack.pop()
            if tag == "ol" and self._ol_counter:
                self._ol_counter.pop()
        elif tag in self._INLINE_WRAPS:
            self._parts.append(self._INLINE_WRAPS[tag])

    def handle_data(self, data: str) -> None:
        self._parts.append(data)

    # --- output ---------------------------------------------------------

    def to_markdown(self) -> str:
        text = "".join(self._parts)
        text = _decode_entities(text)
        # 折叠多余空行，最多保留一空行
        text = re.sub(r"\n{3,}", "\n\n", text)
        return text.strip()


def html_to_markdown(html: str) -> str:
    """LeetCode 题面 HTML → Markdown。失败时返回原字符串。"""
    if not html:
        return ""
    try:
        parser = _LeetcodeToMarkdown()
        parser.feed(html)
        parser.close()
        return parser.to_markdown()
    except Exception:
        return html


_EXAMPLE_ANCHOR_RE = re.compile(
    r'<strong[^>]*class="example"[^>]*>\s*Example\s*(\d+)\s*:?\s*</strong>',
    re.IGNORECASE,
)

_PRE_BLOCK_RE = re.compile(r"<pre>(.*?)</pre>", re.DOTALL | re.IGNORECASE)

_PARAGRAPH_RE = re.compile(r"<p[^>]*>(.*?)</p>", re.DOTALL | re.IGNORECASE)

_EXAMPLE_LABEL_RE = re.compile(
    r"<strong>\s*(Input|Output|Explanation)\s*:?\s*</strong>",
    re.IGNORECASE,
)

_EXAMPLE_IO_SPAN_RE = re.compile(
    r'<span[^>]*class="example-io"[^>]*>(.*?)</span>',
    re.DOTALL | re.IGNORECASE,
)

_CONSTRAINTS_ANCHOR_RE = re.compile(
    r"<p[^>]*>\s*<strong>\s*Constraints",
    re.IGNORECASE,
)


def _strip_tags(text: str) -> str:
    """粗暴去 HTML 标签留纯文本,用于 <pre>/<span> 内文解包。"""
    return re.sub(r"<[^>]+>", "", text)


def extract_examples(html: str) -> List[Dict[str, str]]:
    """从 LeetCode 题面里抽出结构化 examples。

    同时处理两种历史格式:
      1. 老格式: <strong class="example">Example N:</strong><pre>Input/Output/...</pre>
      2. 新格式(3xxx 新题): <strong class="example">...</strong><div class="example-block">
         <p><strong>Input:</strong> <span class="example-io">...</span></p>...</div>

    返回: ``[{"index": 1, "input": "...", "output": "...", "explanation": "..."}, ...]``
    匹配不到时返回空列表。``explanation`` 字段仅在有时出现。
    """
    if not html:
        return []

    anchors = list(_EXAMPLE_ANCHOR_RE.finditer(html))
    if not anchors:
        return []

    examples: List[Dict[str, str]] = []
    for idx, anchor in enumerate(anchors):
        region_start = anchor.end()
        if idx + 1 < len(anchors):
            region_end = anchors[idx + 1].start()
        else:
            constraints = _CONSTRAINTS_ANCHOR_RE.search(html, region_start)
            region_end = constraints.start() if constraints else len(html)
        region = html[region_start:region_end]

        fields = _parse_pre_style(region) or _parse_paragraph_style(region)
        if not fields.get("input") and not fields.get("output"):
            continue

        example: Dict[str, str] = {
            "index": int(anchor.group(1)),
            "input": fields.get("input", ""),
            "output": fields.get("output", ""),
        }
        if fields.get("explanation"):
            example["explanation"] = fields["explanation"]
        examples.append(example)
    return examples


def _parse_pre_style(region: str) -> Dict[str, str]:
    """老格式:<pre>Input: xxx\\nOutput: yyy\\nExplanation: zzz</pre>"""
    match = _PRE_BLOCK_RE.search(region)
    if not match:
        return {}
    body = _decode_entities(_strip_tags(match.group(1)))
    return _parse_example_body(body)


def _parse_paragraph_style(region: str) -> Dict[str, str]:
    """新格式:<div class="example-block"> 里的 <p><strong>Label:</strong> <span class="example-io">...</span></p>。"""
    fields: Dict[str, str] = {}
    for paragraph in _PARAGRAPH_RE.finditer(region):
        inner = paragraph.group(1)
        label_match = _EXAMPLE_LABEL_RE.search(inner)
        if not label_match:
            continue
        label = label_match.group(1).lower()
        after_label = inner[label_match.end():]
        span_match = _EXAMPLE_IO_SPAN_RE.search(after_label)
        if span_match:
            value = _decode_entities(_strip_tags(span_match.group(1))).strip()
        else:
            value = _decode_entities(_strip_tags(after_label)).strip()
        if value:
            fields[label] = value
    return fields


def _parse_example_body(body: str) -> Dict[str, str]:
    """从 "Input: xx\\nOutput: yy\\nExplanation: zz" 形式的纯文本拆出字段。"""
    # 按段首的 Input:/Output:/Explanation: 切分（大小写不敏感）
    parts = re.split(r"(?im)^\s*(Input|Output|Explanation)\s*:\s*", body)
    fields: Dict[str, str] = {}
    # split 结果: [before, key1, val1, key2, val2, ...]
    for i in range(1, len(parts), 2):
        if i + 1 >= len(parts):
            break
        key = parts[i].strip().lower()
        value = parts[i + 1].strip()
        fields[key] = value
    return fields
