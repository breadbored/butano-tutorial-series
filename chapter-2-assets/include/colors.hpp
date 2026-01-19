/*
 * Copyright (c) 2026 BreadCodes brad@bread.codes
 * MIT License @ LICENSE.md file.
 */

#include "bn_color.h"
#include "bn_sprite_palette_item.h"
#include "bn_sprite_palette_ptr.h"
#include "bn_span.h"

 namespace bread {
    #include "tonc_types.h"

    /**
     * \brief Convert RGB888 to RGB555
     *
     * Color accuracy is lost in this process
     */
    bn::color rgb888_to_bn_color(u8 r, u8 g, u8 b) {
        return bn::color(
            r >> 3,
            g >> 3,
            b >> 3
        );
    }

    bn::sprite_palette_item single_color_palette(bn::color color) {
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
        bn::span<bn::color> fill_16_color_palette(
            bn::color *arr,
            bn::color a,
            bn::color b,
            bn::color c,
            bn::color d
        ) {
            arr[0] = bn::color(0, 0, 0);

            for (u8 i = 1; i < 16; i++) {
                switch ((i - 1) & 3) {
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
                    default:
                        break;
                }
            }

            const bn::span<bn::color> colors_span(arr, 16);

            return colors_span;
        }

        /**
        * \brief DIM-4
        * https://lospec.com/palette-list/dim-4
        *
        * An orange shifted palette
        */
        namespace DIM4 {
            bn::color colors_arr[16];

            /**
            * @brief
            *
            * #201616
            *
            * A slightly orange ebony, resembling brown
            */
            const bn::color bitter_black = rgb888_to_bn_color(
                0x20, 0x16, 0x16
            );

            /**
            * @brief
            *
            * #de422c
            *
            * A bold orange
            */
            const bn::color orange_punch = rgb888_to_bn_color(
                0xDE, 0x42, 0x2C
            );

            /**
            * @brief
            *
            * #f47a64
            *
            * A desaturated orange
            */
            const bn::color salmon_orange = rgb888_to_bn_color(
                0xF4, 0x7A, 0x64
            );

            /**
            * @brief
            *
            * #f0c8a0
            *
            * A creamy, desaturated orange
            */
            const bn::color rustic_peach = rgb888_to_bn_color(
                0xF0, 0xC8, 0xA0
            );

            const bn::sprite_palette_item sprite_palette_item = bn::sprite_palette_item(
                fill_16_color_palette(
                    colors_arr,
                    rustic_peach,
                    salmon_orange,
                    orange_punch,
                    bitter_black
                ),
                bn::bpp_mode::BPP_4
            );

        };

        /**
        * \brief Coldfire GB
        * https://lospec.com/palette-list/coldfire-gb
        *
        * A 4 color cool and warm palette
        */
        namespace ColdfireGB {
            bn::color colors_arr[16];

            /**
             * @brief
             *
             * #46425e
             *
             * A desaturated navy blue
             */
            const bn::color neutral_navy = rgb888_to_bn_color(
                0x46, 0x42, 0x5E
            );

            /**
             * @brief
             *
             * #5b768d
             *
             * A denim blue
             */
            const bn::color denim_jeans = rgb888_to_bn_color(
                0x5B, 0x76, 0x8D
            );

            /**
             * @brief
             *
             * #d17c7c
             *
             * A desaturated salmon
             */
            const bn::color neutral_salmon = rgb888_to_bn_color(
                0xD1, 0x7C, 0x7C
            );

            /**
             * @brief
             *
             * #f6c6a8
             *
             * A creamy, desaturated peach
             */
            const bn::color light_peach = rgb888_to_bn_color(
                0xF6, 0xC6, 0xA8
            );

            const bn::sprite_palette_item sprite_palette_item = bn::sprite_palette_item(
                fill_16_color_palette(
                    colors_arr,
                    neutral_navy,
                    denim_jeans,
                    neutral_salmon,
                    light_peach
                ),
                bn::bpp_mode::BPP_4
            );

        };

    };
 };
