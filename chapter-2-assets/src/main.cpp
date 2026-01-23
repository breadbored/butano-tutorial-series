/*
 * Copyright (c) 2026 BreadCodes brad@bread.codes
 * Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License @ LICENSE.md file.
 */

#include "bn_core.h"

#include "bn_bg_palettes.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_tiles_ptr.h"

#include "bn_keypad.h"

#include "bn_vector.h"
#include "bn_string.h"

#include "felt_32x32_font.hpp"

#include "bn_sprite_items_klotski_blocks.h"

#include "colors.hpp"
#include "types.hpp"

int main()
{
    bn::core::init();

    bn::bg_palettes::set_transparent_color(
        bread::palettes::VIVIDMEMORY8::creamy_white
    );

    // Chapter Name
    bn::sprite_text_generator text_generator(
        fonts::felt_32x32_sprite_font,
        bread::palettes::VIVIDMEMORY8::sprite_palette_item
    );
    text_generator.set_center_alignment();
    bn::string<15> title_message_string = "Assets";
    bn::vector<bn::sprite_ptr, 15> title_message_sprites;
    text_generator.generate(
        0, -60,
        title_message_string,
        title_message_sprites
    );

    // Chapter Number (I increased the vector size. you'll see why later)
    bn::string<17> subtitle_message_string = "Chapter 2";
    bn::vector<bn::sprite_ptr, 17> subtitle_message_sprites;
    text_generator.generate(
        0, -40,
        subtitle_message_string,
        subtitle_message_sprites
    );

    // Chapter 2 code

    // This is a "Sprite Item," which is the definition of the sprite.
    bn::sprite_item block_sprite_item = bn::sprite_items::klotski_blocks;

    // Every "Sprite Item" is the source, and we use the Sprite Item to make a "Sprite Pointer,"
    // which is a "smart pointer" that will continue to exist as long as it is in an active scope
    // (again, we'll cover scopes later, but just know it has to still be accessible to stay alive)
    bn::sprite_ptr block = block_sprite_item.create_sprite(0, 0);
    // You will now see the above sprite on screen at position (0,0) at the center of the screen

    // Let's make a few more, and manage them in a vector (a list)
    bn::vector<bn::sprite_ptr, 5> block_list;
    for (int i = 0; i < block_list.max_size(); i++) {
        // I'm going to do a magic trick here...
        // The GBA CPU doesn't know what division is, so if you do a division
        // with `/`, it does some compiler magic to make it work. This is SLOW.
        //
        // However, if the denominator is a power of 2 (2, 4, 8, 16, 32, 64, 128, 256, etc),
        // you can right-shift the bits once to divide by 2. Right-shift them twice to divide by 4.
        // Right-shift them 3 times to divide by 8. Etc, etc. This is fast, and bypasses this limitation.
        //
        // All that to say, the following can also be read as `block_list.max_size() / 2`
        const u8 half_size = block_list.max_size() >> 1;
        const s8 adjusted_x_index = -half_size + i;

        // I'm just giving the index a name to reduce confusion shortly
        const u8 sprite_index = i;

        // Add the block to the list
        block_list.push_back(
            block_sprite_item.create_sprite(
                adjusted_x_index * 40,
                48
            )
        );
        // Tell the sprite to use the tile at `sprite_index`
        block_list.at(i).set_tiles(
            block_sprite_item.tiles_item().create_tiles(sprite_index)
        );
    }

    // You will now see all 7 sprites.
    // 1 above, 6 below from the list using different tiles from the spritesheet


    while(true)
    {
        // Let's listen for when the A button is pressed
        if (bn::keypad::a_pressed()) {
            // when pressed (the first frame down), change the header text

            // title
            title_message_sprites.clear();
            text_generator.generate(
                0, -60,
                "Congrats!",
                title_message_sprites
            );
            // subtitle
            subtitle_message_sprites.clear();
            text_generator.generate(
                0, -40,
                "You did Chapter 2",
                subtitle_message_sprites
            );
        }

        bn::core::update();
    }
}
