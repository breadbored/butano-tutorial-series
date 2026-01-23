/*
 * Copyright (c) 2026 BreadCodes brad@bread.codes
 * Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License @ LICENSE.md file.
 */

#include "bn_core.h"
#include "bn_bg_palettes.h"
#include "types.hpp"

#include "bn_regular_bg_map_cell.h"
#include "bn_regular_bg_map_cell_info.h"
#include "bn_regular_bg_map_item.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_tiles_items_container.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_map_ptr.h"

#include "bn_vector.h"

#include "types.hpp"
#include "block.hpp"
#include "cursor.hpp"
#include "colors.hpp"
#include "container.hpp"

void game_scene() {
    bn::bg_palettes::set_transparent_color(
        bread::palettes::VIVIDMEMORY8::blue
    );

    // This is sorta how our levels will be built
    // This is just for a draft
    const u8 NUM_BLOCKS = 5;
    const LevelPair level_blocks[NUM_BLOCKS] = {
        // Block 1
        LevelPair(
            BlockType::BlockType_DoubleWideY,
            { 0, 0 }
        ),
        // Block 2
        LevelPair(
            BlockType::BlockType_DoubleWideY,
            { 16, 0 }
        ),
        // Block 3
        LevelPair(
            BlockType::BlockType_DoubleWideY,
            { -16, 0 }
        ),
        // Block 4
        LevelPair(
            BlockType::BlockType_DoubleWideX,
            { -16, -24 }
        ),
        // Block 5
        LevelPair(
            BlockType::BlockType_DoubleWideX,
            { 16, -24 }
        ),
    };

    // Set up the container
    // The container is a constructor for our gameplay scene
    Container<NUM_BLOCKS> container = Container<NUM_BLOCKS>(16, 16, level_blocks, 5);

    while(true)
    {
        container.update(); // we will tell the container when a frame is drawn
        bn::core::update();
    }
}
