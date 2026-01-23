/*
 * Copyright (c) 2026 BreadCodes brad@bread.codes
 * MIT License @ LICENSE.md file.
 */

#ifndef BREAD_COLORS_HPP
#define BREAD_COLORS_HPP

#include "bn_color.h"
#include "bn_sprite_palette_item.h"
#include "bn_sprite_palette_ptr.h"
#include "bn_bg_palette_item.h"
#include "bn_span.h"

namespace bread {
    #include "tonc_types.h"

    /**
     * \brief Convert RGB888 to RGB555
     *
     * Color accuracy is lost in this process
     */
    inline bn::color rgb888_to_bn_color(u8 r, u8 g, u8 b) {
        return bn::color(
            r >> 3,
            g >> 3,
            b >> 3
        );
    }

    inline bn::sprite_palette_item single_color_palette(bn::color color) {
       bn::color colors_arr[16] = {
           color, color, color, color,
           color, color, color, color,
           color, color, color, color,
           color, color, color, color,
       };
       bn::span<bn::color> colors_span(colors_arr, 16);
       return bn::sprite_palette_item(colors_span, bn::bpp_mode::BPP_4);
    }

    /**
     * \brief Color palettes I've assembled from lospec.com!
     */
    namespace palettes {
        inline bn::span<bn::color> fill_16_color_palette(
            bn::color *arr,
            bn::color a,
            bn::color b,
            bn::color c,
            bn::color d,
            bn::color e,
            bn::color f,
            bn::color g,
            bn::color h
        ) {
            arr[0] = bn::color(0, 0, 0);

            for (u8 i = 1; i < 16; i++) {
                switch ((i - 1) & 7) {
                    case 0: {
                        arr[i] = a;
                        break;
                    }
                    case 1: {
                        arr[i] = b;
                        break;
                    }
                    case 2: {
                        arr[i] = c;
                        break;
                    }
                    case 3: {
                        arr[i] = d;
                        break;
                    }
                    case 4: {
                        arr[i] = e;
                        break;
                    }
                    case 5: {
                        arr[i] = f;
                        break;
                    }
                    case 6: {
                        arr[i] = g;
                        break;
                    }
                    case 7: {
                        arr[i] = h;
                        break;
                    }
                    default:
                        break;
                }
            }

            const bn::span<bn::color> colors_span(arr, 16);

            return colors_span;
        }

        /**
        * \brief VIVIDMEMORY8
        * https://lospec.com/palette-list/vividmemory8
        *
        * A 4 color cool and warm palette
        */
        namespace VIVIDMEMORY8 {
            inline bn::color colors_arr[16];
            inline bn::color bg_colors_arr[16];

            /**
             * @brief
             *
             * #381631
             *
             * Deep Dark Maroon
             */
            const bn::color deep_dark_maroon = rgb888_to_bn_color(
                0x38, 0x16, 0x31
            );

            /**
             * @brief
             *
             * #d8dcb4
             *
             * A creamy white
             */
            const bn::color creamy_white = rgb888_to_bn_color(
                0xD8, 0xDC, 0xB4
            );

            /**
             * @brief
             *
             * #e21c61
             *
             * Red
             */
            const bn::color red = rgb888_to_bn_color(
                0xE2, 0x1C, 0x61
            );

            /**
             * @brief
             *
             * #e26159
             *
             * An orange
             */
            const bn::color orange = rgb888_to_bn_color(
                0xE2, 0x61, 0x59
            );

            /**
             * @brief
             *
             * #fea85f
             *
             * A yellow
             */
            const bn::color yellow = rgb888_to_bn_color(
                0xFE, 0xA8, 0x5F
            );

            /**
             * @brief
             *
             * #105390
             *
             * A dark blue
             */
            const bn::color dark_blue = rgb888_to_bn_color(
                0x10, 0x53, 0x90
            );

            /**
             * @brief
             *
             * #1b958d
             *
             * A blue
             */
            const bn::color blue = rgb888_to_bn_color(
                0x1B, 0x95, 0x8D
            );

            /**
             * @brief
             *
             * #5eb6ad
             *
             * A cyan
             */
            const bn::color cyan = rgb888_to_bn_color(
                0x5E, 0xB6, 0xAD
            );

            const bn::sprite_palette_item sprite_palette_item = bn::sprite_palette_item(
                fill_16_color_palette(
                    colors_arr,
                    deep_dark_maroon,
                    red,
                    orange,
                    yellow,
                    dark_blue,
                    blue,
                    cyan,
                    creamy_white
                ),
                bn::bpp_mode::BPP_4
            );

            const bn::bg_palette_item bg_palette_item = bn::bg_palette_item(
                fill_16_color_palette(
                    bg_colors_arr,
                    yellow,
                    deep_dark_maroon,
                    orange,
                    red,
                    dark_blue,
                    blue,
                    cyan,
                    creamy_white
                ),
                bn::bpp_mode::BPP_4
            );

        };

    };
};

#endif
