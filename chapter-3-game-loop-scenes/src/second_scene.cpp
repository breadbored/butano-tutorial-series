/*
 * Copyright (c) 2026 BreadCodes brad@bread.codes
 * Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License @ LICENSE.md file.
 */

 #include "colors.hpp"

 #include "fonts/felt_32x32_font.hpp"

 #include "bn_core.h"
 #include "bn_keypad.h"
 #include "bn_sprite_ptr.h"
 #include "bn_sprite_item.h"
 #include "bn_sprite_text_generator.h"
 #include "bn_string.h"
 #include "bn_bg_palettes.h"

void second_scene() {
    bn::bg_palettes::set_transparent_color(
        bread::palettes::ColdfireGB::neutral_navy
    );

    // Make a new sprite palette to change the font color
    const bn::sprite_palette_item sprite_palette_item = bn::sprite_palette_item(
        bread::palettes::fill_16_color_palette(
            bread::palettes::ColdfireGB::colors_arr,
            bread::palettes::ColdfireGB::neutral_salmon,
            bread::palettes::ColdfireGB::light_peach,
            bread::palettes::ColdfireGB::neutral_navy,
            bread::palettes::ColdfireGB::denim_jeans
        ),
        bn::bpp_mode::BPP_4
    );

    bn::sprite_text_generator text_generator(
        fonts::felt_32x32_sprite_font,
        sprite_palette_item
    );
    text_generator.set_center_alignment();
    bn::string<6> title_message_string = "Scenes";
    bn::vector<bn::sprite_ptr, 6> title_message_sprites;
    text_generator.generate(
        0, -60,
        title_message_string,
        title_message_sprites
    );

    bn::string<9> subtitle_message_string = "Chapter 3";
    bn::vector<bn::sprite_ptr, 9> subtitle_message_sprites;
    text_generator.generate(
        0, -40,
        subtitle_message_string,
        subtitle_message_sprites
    );

    bn::string<23> button_message_string = "You are in a new scene!";
    bn::vector<bn::sprite_ptr, 23> button_message_sprites;
    text_generator.generate(
        0, 0,
        button_message_string,
        button_message_sprites
    );

    while(true)
    {
        bn::core::update(); // draw the frame otherwise
    }
}
