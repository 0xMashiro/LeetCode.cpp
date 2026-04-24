from datetime import datetime
from enum import Enum
from typing import Optional


class ColorCode(Enum):
    BLACK = "30"
    RED = "31"
    GREEN = "32"
    YELLOW = "33"
    BLUE = "34"
    MAGENTA = "35"
    CYAN = "36"
    WHITE = "37"
    RESET = "0"


def color_text(text, text_color):
    return f"\033[{text_color}m{text}\033[0m"


def log_with_time(message: str, color: Optional[ColorCode] = None) -> None:
    """打印带时间戳的日志（统一入口，替代各模块内自建的实现）"""
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    if color:
        message = color_text(message, color.value)
    print(f"[{timestamp}] {message}")
