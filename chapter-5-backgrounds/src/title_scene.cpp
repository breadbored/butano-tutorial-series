/*
 * Copyright (c) 2026 BreadCodes brad@bread.codes
 * Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License @ LICENSE.md file.
 */

#include "colors.hpp"

#include "globals.hpp"

#include "fonts/marker_16x16_font.hpp"

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_item.h"
#include "bn_sprite_text_generator.h"
#include "bn_string.h"
#include "bn_regular_bg_ptr.h"

#include "bn_regular_bg_items_level_1_title_art.h"

#include "types.hpp"

void title_scene() {

    bn::regular_bg_ptr title_card = bn::regular_bg_items::level_1_title_art.create_bg(0, 0);

    bn::sprite_text_generator text_generator(
        fonts::marker_16x16_sprite_font,
        bread::palettes::VIVIDMEMORY8::sprite_palette_item
    );

    text_generator.set_center_alignment();

    bn::string<9> subtitle_message_string = "Chapter 5";
    bn::vector<bn::sprite_ptr, 9> subtitle_message_sprites;
    text_generator.generate(
        0, 40,
        subtitle_message_string,
        subtitle_message_sprites
    );

    bn::string<19> title_message_string = "Backgrounds & Tiles";
    bn::vector<bn::sprite_ptr, 19> title_message_sprites;
    text_generator.generate(
        0, 56,
        title_message_string,
        title_message_sprites
    );

    // Show for 240 frames
    for (int i = 0; i < 240; i++) {
        bn::core::update();
    }

    scene = SceneEnum::ButanoScene; // update the scene
    bn::core::update(); // give the final update
}
