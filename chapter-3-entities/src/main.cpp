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
#include "bn_math.h"

#include "felt_32x32_font.hpp"

#include "bn_sprite_items_klotski_blocks.h"

#include "colors.hpp"
#include "types.hpp"
#include "block.hpp"
#include "cursor.hpp"

int main()
{
    bn::core::init();

    bn::bg_palettes::set_transparent_color(
        bread::palettes::ColdfireGB::neutral_salmon
    );

    Cursor cursor = Cursor({0, -32});

    bn::vector<Block, 5> block_list;

    for (int i = 0; i < block_list.max_size(); i++) {
        const u8 half_max = block_list.max_size() >> 1;
        const s8 x_offset = -half_max + i;

        block_list.push_back(
            Block({
                x_offset * 40, // x
                0  // y
            })
        );
    }

    while(true)
    {
        if (cursor.searching_for_block) {
            // check if the cursor is over a block
            for (int i = 0; i < block_list.size(); i++) {
                auto block = &block_list.at(i);
                bn::point distance = {
                    block->position.x() - cursor.position.x(),
                    block->position.y() - cursor.position.y()
                };

                if (bn::abs(distance.x()) < 32 && bn::abs(distance.y()) < 32) {
                    cursor.grab_block(block);
                    break; // we found one, stop searching
                }
            }
        }

        // every frame we need to tell our entities to update
        cursor.update();
        for (int i = 0; i < block_list.size(); i++) {
            auto block = &block_list.at(i);
            block->update();
        }
        bn::core::update();
    }
}
