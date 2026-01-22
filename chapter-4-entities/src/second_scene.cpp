/*
 * Copyright (c) 2026 BreadCodes brad@bread.codes
 * Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License @ LICENSE.md file.
 */

#include "bn_core.h"

#include "bn_bg_palettes.h"

#include "bn_vector.h"

#include "colors.hpp"
#include "types.hpp"
#include "block.hpp"
#include "cursor.hpp"

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

int second_scene()
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
            Block(level_blocks[i].second, level_blocks[i].first)
        );
    }

    cursor.block_vec = &block_list;

    while(true)
    {
        // every frame we need to tell our entities a new frame is being drawn
        cursor.update();
        for (int i = 0; i < block_list.size(); i++) {
            auto block = &block_list.at(i);
            block->update();
        }
        bn::core::update();
    }
}
