/*
 * Copyright (c) 2026 BreadCodes brad@bread.codes
 * Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License @ LICENSE.md file.
 */

 #include "colors.hpp"

 #include "globals.hpp"

 #include "fonts/felt_32x32_font.hpp"

 #include "bn_core.h"
 #include "bn_keypad.h"
 #include "bn_sprite_ptr.h"
 #include "bn_sprite_item.h"
 #include "bn_sprite_text_generator.h"
 #include "bn_string.h"

void title_scene() {
    bn::sprite_text_generator text_generator(
        fonts::felt_32x32_sprite_font,
        bread::palettes::ColdfireGB::sprite_palette_item
    );
    text_generator.set_center_alignment();
    bn::string<8> title_message_string = "Entities";
    bn::vector<bn::sprite_ptr, 8> title_message_sprites;
    text_generator.generate(
        0, -60,
        title_message_string,
        title_message_sprites
    );

    bn::string<9> subtitle_message_string = "Chapter 4";
    bn::vector<bn::sprite_ptr, 9> subtitle_message_sprites;
    text_generator.generate(
        0, -40,
        subtitle_message_string,
        subtitle_message_sprites
    );

    bn::string<16> button_message_string = "Press any button";
    bn::vector<bn::sprite_ptr, 16> button_message_sprites;
    text_generator.generate(
        0, 0,
        button_message_string,
        button_message_sprites
    );

    while(true)
    {
        // Let's listen for when any button is pressed
        if (bn::keypad::any_pressed()) {
            scene = SceneEnum::SecondScene; // update the scene
            bn::core::update(); // give the final update
            break; // exit the scene loop
        }

        bn::core::update(); // draw the frame otherwise
    }
}
