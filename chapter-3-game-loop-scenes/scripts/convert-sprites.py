"""
Copyright (c) 2026 BreadCodes brad@bread.codes
Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License @ LICENSE.md file.
"""

import json
import os
import re
from pathlib import Path

from PIL import Image


def find_color_depth_and_unused_color(
    img_data_rgba,
) -> tuple[int, tuple[int, int, int] | None]:
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

    return (color_depth, unused_color)


reg = re.compile(r"\.[a-zA-Z]+$")

if __name__ == "__main__":
    root_dir = Path("./")

    if len(os.listdir(root_dir / "sprites")) > 0:
        print("\n\nStarting EXTTOOL asset conversion")

    for file in os.listdir(root_dir / "sprites"):
        file_without_ext = re.split(reg, file)[0]
        full_path = root_dir / "sprites" / file

        bmp_file_name = file_without_ext + ".bmp"
        bmp_path = root_dir / "graphics" / bmp_file_name

        json_path = root_dir / "graphics" / (file_without_ext + ".json")

        print(
            "Converting",
            file,
            "@",
            full_path,
            "to:\n",
            "   ",
            bmp_path,
            "\n   +",
            json_path,
        )

        img = Image.open(full_path).convert("RGBA")

        width = img.width
        height = img.height

        if width not in [8, 16, 32, 64]:
            raise Exception("""This is not a spritesheet arranged vertically with one of the following tile sizes:
    - 8x8
    - 16x16
    - 32x32
    - 64x64

    If you have an irregularly sized sprite you must fit it into one of the above sizes.
    Let's say your sprite is 24x14, then it must be put into a 32x32 sprite.""")
        if height % width != 0:
            raise Exception("""This is not a spritesheet arranged vertically with one of the following tile sizes:
    - 8x8
    - 16x16
    - 32x32
    - 64x64

    If you have an irregularly sized sprite you must fit it into one of the above sizes.
    Let's say your sprite is 24x14, then it must be put into a 32x32 sprite.

    If you have a 8x8 sprite with 3 frames, the dimensions should be 8x24, where it is a vertical strip of sprite tiles.""")

        color_depth, unused_color = find_color_depth_and_unused_color(img.getdata())

        # unlikely, but if true, we have a problem
        if not unused_color:
            raise ValueError(f"Could not find an unused color in {full_path}")

        # get transparent pixel indexes so that we can convert to the unused index 0 color
        transparent_indexes = [
            i
            for i, pixel in enumerate(img.getdata())  # pyright: ignore[reportArgumentType]
            if pixel[3] == 0
        ]

        # convert the image to 'P' mode and quantize it to the specified color depth
        img = img.convert("RGB").quantize(colors=color_depth)
        palette = img.getpalette()

        if not palette:
            raise Exception(
                "Quantized image doesn't have a palette??? (shouldn't happen)"
            )

        # create a new palette with the unused color as the first color
        new_palette = [unused_color[0], unused_color[1], unused_color[2]] + palette[
            : 3 * (color_depth - 1)
        ]
        img.putpalette(new_palette)

        # adjust the pixel data to shift indices by one
        img_data = img.getdata()
        shifted_data = [1 if pixel == 0 else pixel + 1 for pixel in img_data]  # pyright: ignore[reportOperatorIssue]
        # if the pixel is transparent, set it to 0
        for i in transparent_indexes:
            shifted_data[i] = 0
        img.putdata(shifted_data)

        # set the transparency color to the first entry in the palette
        img.info["transparency"] = 0

        # save the BMP image
        img.save(bmp_path, format="BMP")

        # save the requisite Butano JSON file
        # this is necessary
        with open(json_path, "w") as f:
            json.dump({"type": "sprite", "height": width, "width": width}, f)

    print("\n\n")
