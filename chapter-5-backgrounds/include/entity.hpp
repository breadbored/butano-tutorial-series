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
    Entity(bn::sprite_item _sprite_item, bn::point _position)
        : sprite_item(_sprite_item),
          p_sprite(_sprite_item.create_sprite(_position)),
          position(_position)
    {}

    virtual ~Entity() {
        // called on destroy!
    }

    /**
     * @brief Call this every frame
     */
    virtual void update() {
        this->p_sprite.set_position(position);
    }

    bn::sprite_item sprite_item;
    bn::sprite_ptr p_sprite;
    bn::point position = {
        0, // x
        0  // y
    };

private:
};

#endif
