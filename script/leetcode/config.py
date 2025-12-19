from dataclasses import dataclass
from enum import Enum

from template import (
    INCLUDE_TEMPLATE,
    SOURCE_TEMPLATE,
    TEST_TEMPLATE,
    DESIGN_INCLUDE_TEMPLATE,
    DESIGN_SOURCE_TEMPLATE,
    DESIGN_TEST_TEMPLATE,
)


@dataclass
class FileTypeInfo:
    folder: str
    placeholder: str
    template: str
    design_template: str = ""  # 设计类题目的模板


class FileTypeConfig(Enum):
    HEADER = FileTypeInfo(
        folder="include/leetcode/problems/",
        placeholder="include/leetcode/problems/{}.h",
        template=INCLUDE_TEMPLATE,
        design_template=DESIGN_INCLUDE_TEMPLATE,
    )
    SOURCE = FileTypeInfo(
        folder="src/leetcode/problems/",
        placeholder="src/leetcode/problems/{}.cpp",
        template=SOURCE_TEMPLATE,
        design_template=DESIGN_SOURCE_TEMPLATE,
    )
    TEST = FileTypeInfo(
        folder="test/leetcode/problems/",
        placeholder="test/leetcode/problems/{}.cpp",
        template=TEST_TEMPLATE,
        design_template=DESIGN_TEST_TEMPLATE,
    )
