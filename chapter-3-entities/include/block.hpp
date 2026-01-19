/*
 * Copyright (c) 2026 BreadCodes brad@bread.codes
 * Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License @ LICENSE.md file.
 */

#ifndef BREAD_BLOCK_HPP
#define BREAD_BLOCK_HPP

#include "bn_point.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_item.h"
#include "bn_sprite_items_klotski_blocks.h"
#include "entity.hpp"
#include "types.hpp"
#include "utils.hpp"

class Block : public Entity {
public:
    Block(bn::point position)
        : Entity(
            bn::sprite_items::klotski_blocks,
            position
          ) {

    }

    /**
     * @brief Call this every frame
     */
    void update() override {
        Entity::update(); // call the underlying Entity's update
    }

    LockedAxis locked_axis = LockedAxis::NoAxis;

private:

};

#endif
