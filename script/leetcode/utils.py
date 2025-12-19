from enum import Enum

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
