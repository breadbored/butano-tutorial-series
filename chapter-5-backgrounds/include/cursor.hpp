/*
 * Copyright (c) 2026 BreadCodes brad@bread.codes
 * Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License @ LICENSE.md file.
 */

#ifndef BREAD_CURSOR_HPP
#define BREAD_CURSOR_HPP

#include "bn_point.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_item.h"
#include "bn_sprite_tiles_ptr.h"
#include "bn_sprite_items_cursor.h"
#include "bn_vector.h"
#include "entity.hpp"
#include "types.hpp"
#include "block.hpp"
#include "bn_keypad.h"

// this is a forward declaration
template <u8 NUM_BLOCKS>
class Container;
// this is saying "we promise this will be defined later."
// the purpose of the forward declaration is to prevent circular dependencies.
// Container imports Cursor, so Cursor can't import Container.
// If you make this promise, Cursor will trust that this will be defined later.

class Cursor : public Entity {
public:
    Cursor(bn::point position)
        : Entity(
            bn::sprite_items::cursor,
            position
        ) {
        p_sprite.set_z_order(-10);
    }

    /**
     * @brief Call this every frame
     */
    template <u8 NUM_BLOCKS>
    void update(Container<NUM_BLOCKS> *container, bn::vector<Block, NUM_BLOCKS> *block_vec) {
        // When A is pressed, the cursor should find a block to grab
        if (bn::keypad::a_pressed() && grabbed_block == nullptr) {
            for (int i = 0; i < block_vec->size(); i++) {
                auto block = &block_vec->at(i);
                bn::point distance = {
                    block->position.x() - this->position.x(),
                    block->position.y() - this->position.y()
                };

                if (this->over_block(block)) {
                    this->grab_block(block);
                    break; // we found one, stop searching
                }
            }
        }
        if (bn::keypad::a_released() && grabbed_block != nullptr) {
            release_block();
        }

        // If we have a block, let's do something with it
        if (grabbed_block != nullptr) {
            bn::point new_position = position;

            // If the X axis isn't locked, let's move the held block
            if (
                grabbed_block->locked_axis != LockedAxis::XAxis
                && grabbed_block->locked_axis != LockedAxis::BothAxis
            ) {
                if (bn::keypad::right_held() || bn::keypad::right_pressed()) {
                    new_position.set_x(new_position.x() + 1);
                } else if (bn::keypad::left_held() || bn::keypad::left_pressed()) {
                    new_position.set_x(new_position.x() - 1);
                }
            }
            // If the Y axis isn't locked, let's move the held block
            if (
                grabbed_block->locked_axis != LockedAxis::YAxis
                && grabbed_block->locked_axis != LockedAxis::BothAxis
            ) {
                if (bn::keypad::up_held() || bn::keypad::up_pressed()) {
                    new_position.set_y(new_position.y() - 1);
                } else if (bn::keypad::down_held() || bn::keypad::down_pressed()) {
                    new_position.set_y(new_position.y() + 1);
                }
            }

            bool collided = false;

            if (block_vec != nullptr) {
                for (int i = 0; i < block_vec->size(); i++) {
                    if (&block_vec->at(i) == grabbed_block) {
                        continue;
                    }
                    if (grabbed_block->collides(&block_vec->at(i), new_position)) {
                        collided = true;
                    }
                }
            }

            // Adding the Container edge collision check
            if (grabbed_block->collides_with_wall(new_position, container->tl(), container->br())) {
                collided = true;
            }

            if (!collided) {
                position.set_x(new_position.x());
                position.set_y(new_position.y());
                grabbed_block->position.set_x(new_position.x());
                grabbed_block->position.set_y(new_position.y());
            }
        } else { // We don't have a block, so let's move around
            if (bn::keypad::right_held() || bn::keypad::right_pressed()) {
                position.set_x(position.x() + 1);
            }
            if (bn::keypad::left_held() || bn::keypad::left_pressed()) {
                position.set_x(position.x() - 1);
            }
            if (bn::keypad::up_held() || bn::keypad::up_pressed()) {
                position.set_y(position.y() - 1);
            }
            if (bn::keypad::down_held() || bn::keypad::down_pressed()) {
                position.set_y(position.y() + 1);
            }
        }

        p_sprite.set_tiles(
            sprite_item.tiles_item().create_tiles(
                grabbed_block == nullptr ? 0 : 1
            )
        );

        Entity::update(); // call the underlying Entity's update
    }

    /**
     * @brief Grab a Block
     */
    void grab_block(Block *block) {
        grabbed_block = block;
        position.set_x(grabbed_block->position.x());
        position.set_y(grabbed_block->position.y());
    }

    bool over_block(Block *other) {
        return (other->position.x() + other->bounds.first.x() <= this->position.x()) &&
               (other->position.y() + other->bounds.first.y() <= this->position.y()) &&
               (other->position.x() + other->bounds.second.x() >= this->position.x()) &&
               (other->position.y() + other->bounds.second.y() >= this->position.y());
    }

private:
    /**
     * @brief A pointer reference to the block grabbed
     */
    Block* grabbed_block = nullptr;

    /**
     * @brief Grab a Block
     */
    void release_block() {
        grabbed_block = nullptr;
    }
};

#endif
