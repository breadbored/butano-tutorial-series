"""
Copyright (c) 2026 BreadCodes brad@bread.codes
Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License @ LICENSE.md file.
"""

import json
import os
import re
from pathlib import Path

from PIL import Image
from utils import find_color_depth_and_unused_color

reg = re.compile(r"\.[a-zA-Z]+$")


def convert_bgs():
    root_dir = Path("./")

    for type in ["tiles", "palettes", "regular"]:
        if len(os.listdir(root_dir / "backgrounds" / type)) > 0:
            print("\n\nStarting EXTTOOL asset conversion")

        for file in os.listdir(root_dir / "backgrounds" / type):
            file_without_ext = re.split(reg, file)[0]
            full_path = root_dir / "backgrounds" / type / file

            bmp_file_name = file_without_ext + ".bmp"
            bmp_path = root_dir / "graphics" / bmp_file_name

            json_path = root_dir / "graphics" / (file_without_ext + ".json")

            print(
                "Converting",
                type,
                "",
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

            if type == "tiles":
                if height not in [8, 16, 32, 64]:
                    raise Exception("""Background tiles must be 8x8 each""")
                if width % height != 0:
                    raise Exception("""Background tiles must be 8x8 each""")
            elif type == "regular":
                pass
            elif type == "palettes":
                pass

            color_depth, unused_color, num_colors = find_color_depth_and_unused_color(
                img.getdata()
            )

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
                if type == "tiles":
                    json.dump(
                        {
                            "type": "regular_bg_tiles",
                            "bpp_mode": "bpp_4" if color_depth == 16 else "bpp_8",
                        },
                        f,
                    )
                elif type == "regular":
                    json.dump(
                        {
                            "type": "regular_bg",
                        },
                        f,
                    )
                elif type == "palettes":
                    json.dump(
                        {
                            "type": "bg_palette",
                            "bpp_mode": "bpp_4" if color_depth == 16 else "bpp_8",
                            "colors_count": num_colors,
                        },
                        f,
                    )

            print("\n\n")
