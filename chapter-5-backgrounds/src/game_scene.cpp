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
#include "container_tiles.hpp"

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

const u8 CONTAINER_BG_WIDTH = 32;
const u8 CONTAINER_BG_HEIGHT = 32;

void game_scene() {
    bn::bg_palettes::set_transparent_color(
        bread::palettes::VIVIDMEMORY8::blue
    );

    // Set up the background tilemap
    bn::regular_bg_map_cell _ui_cells[CONTAINER_BG_WIDTH * CONTAINER_BG_HEIGHT];
    bn::regular_bg_map_item _map_item = bn::regular_bg_map_item(*_ui_cells, bn::size(CONTAINER_BG_WIDTH, CONTAINER_BG_HEIGHT));
    bn::regular_bg_item _bg_item = bn::regular_bg_item(
        bn::regular_bg_tiles_items::container,
        bread::palettes::VIVIDMEMORY8::bg_palette_item,
        _map_item
    );
    bn::regular_bg_ptr _bg = _bg_item.create_bg(0, 0);

    bread::container_tiles::fill_container(CONTAINER_BG_WIDTH, CONTAINER_BG_HEIGHT, _ui_cells, _map_item, _bg);
    bread::container_tiles::fill_container(CONTAINER_BG_WIDTH, CONTAINER_BG_HEIGHT, _ui_cells, _map_item, _bg);

    // Set up the Cursor we created
    Cursor cursor = Cursor({0, -32});

    // Track the blocks we're going to interact with
    bn::vector<Block, 5> block_list;
    // Init those blocks
    for (int i = 0; i < block_list.max_size(); i++) {
        const u8 half_max = block_list.max_size() >> 1;
        const s8 x_offset = -half_max + i;
        block_list.push_back(
            Block(level_blocks[i].second, level_blocks[i].first)
        );
    }

    // Give cursor reference to the list of blocks
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
