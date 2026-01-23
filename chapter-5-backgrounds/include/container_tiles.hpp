/*
 * Copyright (c) 2026 BreadCodes brad@bread.codes
 * Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License @ LICENSE.md file.
 */

#ifndef BREAD_CONTAINER_TILES_HPP
#define BREAD_CONTAINER_TILES_HPP

#include "types.hpp"

#include "bn_regular_bg_map_cell.h"
#include "bn_regular_bg_map_cell_info.h"
#include "bn_regular_bg_map_item.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_map_ptr.h"

namespace bread {

    namespace container_tiles {

        constexpr u8 CONTAINER_TL = 0;
        constexpr u8 CONTAINER_TL_RIGHT = 1;
        constexpr u8 CONTAINER_TOP = 2;
        constexpr u8 CONTAINER_TR_LEFT = 3;
        constexpr u8 CONTAINER_TR = 4;
        constexpr u8 CONTAINER_TL_BOTTOM = 5;
        constexpr u8 CONTAINER_TL_CORNER = 6;
        constexpr u8 CONTAINER_CAP_LEFT = 7;
        constexpr u8 CONTAINER_TR_CORNER = 8;
        constexpr u8 CONTAINER_TR_BOTTOM = 9;
        constexpr u8 CONTAINER_LEFT = 10;
        constexpr u8 CONTAINER_CAP_DOWN = 11;
        constexpr u8 CONTAINER_BLANK = 12;
        constexpr u8 CONTAINER_CAP_UP = 13;
        constexpr u8 CONTAINER_RIGHT = 14;
        constexpr u8 CONTAINER_BL_TOP = 15;
        constexpr u8 CONTAINER_BL_CORNER = 16;
        constexpr u8 CONTAINER_CAP_RIGHT = 17;
        constexpr u8 CONTAINER_BR_CORNER = 18;
        constexpr u8 CONTAINER_BR_TOP = 19;
        constexpr u8 CONTAINER_BL = 20;
        constexpr u8 CONTAINER_BL_RIGHT = 21;
        constexpr u8 CONTAINER_B = 22;
        constexpr u8 CONTAINER_BR_LEFT = 23;
        constexpr u8 CONTAINER_BR = 24;

        void fill_container(
            u8 width,
            u8 height,
            bn::regular_bg_map_cell *_ui_cells,
            bn::regular_bg_map_item &_map_item,
            bn::regular_bg_ptr &_bg
        ) {
            __builtin_memset(_ui_cells, 0, sizeof(_ui_cells));
            for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {
                    bn::regular_bg_map_cell &current_cell = _ui_cells[_map_item.cell_index(x, y)];
                    bn::regular_bg_map_cell_info current_cell_info(current_cell);
                    current_cell_info.set_tile_index(0);
                    current_cell = current_cell_info.cell();
                }
            }
            bn::regular_bg_map_ptr bg_map = _bg.map();
            bg_map.reload_cells_ref();
        }

        void build_container(
            u8 width,
            u8 height,
            bn::regular_bg_map_cell *_ui_cells,
            bn::regular_bg_map_item &_map_item,
            bn::regular_bg_ptr &_bg
        ) {
            for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {
                    bn::regular_bg_map_cell &current_cell = _ui_cells[_map_item.cell_index(x, y)];
                    bn::regular_bg_map_cell_info current_cell_info(current_cell);
                    current_cell_info.set_tile_index(0);
                    current_cell = current_cell_info.cell();
                }
            }
            bn::regular_bg_map_ptr bg_map = _bg.map();
            bg_map.reload_cells_ref();
        }

    };

};

#endif
