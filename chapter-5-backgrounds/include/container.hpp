/*
 * Copyright (c) 2026 BreadCodes brad@bread.codes
 * Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License @ LICENSE.md file.
 */

#ifndef BREAD_CONTAINER_HPP
#define BREAD_CONTAINER_HPP

#include "types.hpp"

#include "bn_regular_bg_map_cell.h"
#include "bn_regular_bg_map_cell_info.h"
#include "bn_regular_bg_map_item.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_map_ptr.h"
#include "bn_regular_bg_tiles_items_container.h"
#include "bn_assert.h"

#include "bn_vector.h"

#include "colors.hpp"
#include "container_tiles.hpp"
#include "cursor.hpp"
#include "block.hpp"

constexpr u8 CONTAINER_BG_WIDTH = 32;
constexpr u8 CONTAINER_BG_HEIGHT = 32;

template <u8 NUM_BLOCKS>
class Container {
public:
    Container(u8 width, u8 height, const LevelPair *level_blocks, u8 num_level_blocks)
    : width(width), height(height) {
        // Make sure there's an even width and height of tiles
        BN_ASSERT(width % 2 == 0 && height % 2 == 0, "The tile map must be an even number height and width");

        // Make sure the `level_blocks` length and `NUM_BLOCKS` are the same
        BN_ASSERT(NUM_BLOCKS == num_level_blocks, "The number of blocks differs from the level");

        // Init blocks
        for (int i = 0; i < block_list.max_size(); i++) {
            const u8 half_max = block_list.max_size() >> 1;
            const s8 x_offset = -half_max + i;
            block_list.push_back(
                Block(level_blocks[i].second, level_blocks[i].first)
            );
        }

        // blow out the background with clear tiles
        clear_container(CONTAINER_BG_WIDTH, CONTAINER_BG_HEIGHT, _ui_cells, _map_item, _bg);
        // draw the container
        build_container(CONTAINER_BG_WIDTH, CONTAINER_BG_HEIGHT, width, height, _ui_cells, _map_item, _bg);
    }

    u8 width = 16;
    u8 height = 16;

    // Scene stuff
    Cursor cursor = Cursor({0, -32});
    bn::vector<Block, NUM_BLOCKS> block_list;

    // Render function
    void update() {
        cursor.update(this, &block_list);
        for (int i = 0; i < block_list.size(); i++) {
            auto block = &block_list.at(i);
            block->update();
        }
    }

private:
    // Tilemap details
    bn::regular_bg_map_cell _ui_cells[CONTAINER_BG_WIDTH * CONTAINER_BG_HEIGHT];
    bn::regular_bg_map_item _map_item = bn::regular_bg_map_item(*_ui_cells, bn::size(CONTAINER_BG_WIDTH, CONTAINER_BG_HEIGHT));
    bn::regular_bg_item _bg_item = bn::regular_bg_item(
        bn::regular_bg_tiles_items::container,
        bread::palettes::VIVIDMEMORY8::bg_palette_item,
        _map_item
    );
    bn::regular_bg_ptr _bg = _bg_item.create_bg(0, 0);

    // Private tile drawing utils

    // Clear the background with blank tiles
    static void clear_container(
        u8 width,
        u8 height,
        bn::regular_bg_map_cell *_ui_cells,
        bn::regular_bg_map_item &_map_item,
        bn::regular_bg_ptr &_bg
    ) {
        __builtin_memset(_ui_cells, 0, width * height * sizeof(bn::regular_bg_map_cell));
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                bn::regular_bg_map_cell &current_cell = _ui_cells[_map_item.cell_index(x, y)];
                bn::regular_bg_map_cell_info current_cell_info(current_cell);
                current_cell_info.set_tile_index(CONTAINER_BLANK);
                current_cell = current_cell_info.cell();
            }
        }
        bn::regular_bg_map_ptr bg_map = _bg.map();
        bg_map.reload_cells_ref();
    }

    // Build the frame of the container
    static void build_container(
        u8 max_width,
        u8 max_height,
        u8 width,
        u8 height,
        bn::regular_bg_map_cell *_ui_cells,
        bn::regular_bg_map_item &_map_item,
        bn::regular_bg_ptr &_bg
    ) {
        const u8 half_width = (max_width >> 1) - (width >> 1);
        const u8 half_height = (max_height >> 1) - (height >> 1);

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                bn::regular_bg_map_cell &current_cell = _ui_cells[
                    _map_item.cell_index(x + half_width, y + half_height)
                ];
                bn::regular_bg_map_cell_info current_cell_info(current_cell);

                // outer corners
                if (x == 0 && y == 0) {
                    // Top-Left
                    current_cell_info.set_tile_index(CONTAINER_TL);
                } else if (x == width - 1 && y == 0) {
                    // Top-Right
                    current_cell_info.set_tile_index(CONTAINER_TR);
                } else if (x == 0 && y == height - 1) {
                    // Bottom-Left
                    current_cell_info.set_tile_index(CONTAINER_BL);
                } else if (x == width - 1 && y == height - 1) {
                    // Bottom-Right
                    current_cell_info.set_tile_index(CONTAINER_BR);
                }
                // inner corners
                else if (x == 1 && y == 1) {
                    // Top-Left
                    current_cell_info.set_tile_index(CONTAINER_TL_CORNER);
                } else if (x == width - 2 && y == 1) {
                    // Top-Right
                    current_cell_info.set_tile_index(CONTAINER_TR_CORNER);
                } else if (x == 1 && y == height - 2) {
                    // Bottom-Left
                    current_cell_info.set_tile_index(CONTAINER_BL_CORNER);
                } else if (x == width - 2 && y == height - 2) {
                    // Bottom-Right
                    current_cell_info.set_tile_index(CONTAINER_BR_CORNER);
                }
                // outer corner sides clockwise
                else if (x == 1 && y == 0) {
                    // Top-Left
                    current_cell_info.set_tile_index(CONTAINER_TL_RIGHT);
                } else if (x == width - 1 && y == 1) {
                    // Top-Right
                    current_cell_info.set_tile_index(CONTAINER_TR_BOTTOM);
                } else if (x == 0 && y == height - 2) {
                    // Bottom-Left
                    current_cell_info.set_tile_index(CONTAINER_BL_TOP);
                } else if (x == width - 2 && y == height - 1) {
                    // Bottom-Right
                    current_cell_info.set_tile_index(CONTAINER_BR_LEFT);
                }
                // outer corner sides counter-clockwise
                else if (x == 0 && y == 1) {
                    // Top-Left
                    current_cell_info.set_tile_index(CONTAINER_TL_BOTTOM);
                } else if (x == width - 2 && y == 0) {
                    // Top-Right
                    current_cell_info.set_tile_index(CONTAINER_TR_LEFT);
                } else if (x == 1 && y == height - 1) {
                    // Bottom-Left
                    current_cell_info.set_tile_index(CONTAINER_BL_RIGHT);
                } else if (x == width - 1 && y == height - 2) {
                    // Bottom-Right
                    current_cell_info.set_tile_index(CONTAINER_BR_TOP);
                }
                // sides
                else if (x == 0) {
                    // Left
                    current_cell_info.set_tile_index(CONTAINER_L);
                } else if (x == width - 1) {
                    // Right
                    current_cell_info.set_tile_index(CONTAINER_R);
                } else if (y == 0) {
                    // Left
                    current_cell_info.set_tile_index(CONTAINER_T);
                } else if (y == width - 1) {
                    // Right
                    current_cell_info.set_tile_index(CONTAINER_B);
                }
                // blank
                else {
                    // otherwise, empty
                    current_cell_info.set_tile_index(CONTAINER_BLANK);
                }

                current_cell = current_cell_info.cell();
            }
        }
        bn::regular_bg_map_ptr bg_map = _bg.map();
        bg_map.reload_cells_ref();
    }
};

#endif
