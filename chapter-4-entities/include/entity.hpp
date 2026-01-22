/*
 * Copyright (c) 2026 BreadCodes brad@bread.codes
 * Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License @ LICENSE.md file.
 */

#ifndef BREAD_ENTITY_HPP
#define BREAD_ENTITY_HPP

#include "bn_point.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_item.h"

class Entity {
public:
    Entity(bn::sprite_item sprite_item, bn::point position)
        : sprite_item(sprite_item),
          p_sprite(sprite_item.create_sprite(position)),
          position(position)
    {

    }

    /**
     * @brief Call this every frame
     */
    virtual void update() {
        this->p_sprite.set_position(position);
    }

    bn::point position = {
        0, // x
        0  // y
    };
    bn::sprite_ptr p_sprite;
    bn::sprite_item sprite_item;

private:

};

#endif
