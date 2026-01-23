"""
Copyright (c) 2026 BreadCodes brad@bread.codes
Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License @ LICENSE.md file.
"""


def find_color_depth_and_unused_color(
    img_data_rgba,
) -> tuple[int, tuple[int, int, int] | None, int]:
    used_colors = set([(x[0], x[1], x[2]) for x in img_data_rgba if x[3] == 255])
    color_depth = 16 if len(used_colors) <= 16 else 256

    def _find_unused_color():
        for r in range(256):
            for g in range(256):
                for b in range(256):
                    if (r, g, b) not in used_colors:
                        return (r, g, b)
        return None

    unused_color = _find_unused_color()

    return (color_depth, unused_color, len(used_colors))
