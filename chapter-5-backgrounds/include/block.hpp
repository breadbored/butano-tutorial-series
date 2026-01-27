/*
 * Copyright (c) 2026 BreadCodes brad@bread.codes
 * Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License @ LICENSE.md file.
 */

#ifndef BREAD_BLOCK_HPP
#define BREAD_BLOCK_HPP

#include "bn_point.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_tiles_ptr.h"
#include "bn_sprite_item.h"
#include "bn_sprite_items_klotski_blocks.h"
#include "entity.hpp"
#include "types.hpp"

#include "debug.hpp"

class Block : public Entity {
public:
    Block(bn::point _position, BlockType _block_type)
        : Entity(
            bn::sprite_items::klotski_blocks,
            _position
        ), _type(_block_type) {
        this->init();
    }
    Block(bn::point _position)
        : Entity(
            bn::sprite_items::klotski_blocks,
            _position
        ), _type(BlockType::BlockType_DoubleWideY) {
        this->init();
    }

    ~Block() {
        // called on destroy!
    };

    void init() {
        // set the locked axis
        switch (_type) {
            case BlockType::BlockType_DoubleWideX:
            case BlockType::BlockType_SingleWideX:
                {
                    locked_axis = LockedAxis::YAxis;
                    break;
                }
            case BlockType::BlockType_DoubleWideY:
            case BlockType::BlockType_SingleWideY:
                {
                    locked_axis = LockedAxis::XAxis;
                    break;
                }
            default: {
                locked_axis = LockedAxis::BothAxis;
                break;
            }
        }

        // set the bounds of the block
        switch (_type) {
            case BlockType::BlockType_DoubleWideX: {
                bounds = Box(
                    {-16, -8},
                    { 16,  8}
                );
                break;
            }
            case BlockType::BlockType_SingleWideX: {
                bounds = Box(
                    {-16, -4},
                    { 16,  4}
                );
                break;
            }
            case BlockType::BlockType_DoubleWideY: {
                bounds = Box(
                    {-8, -16},
                    { 8,  16}
                );
                break;
            }
            case BlockType::BlockType_SingleWideY: {
                bounds = Box(
                    {-4, -16},
                    { 4,  16}
                );
                break;
            }
            default: {
                bounds = Box(
                    {-16, -16},
                    { 16,  16}
                );
                break;
            }
        }

        p_sprite.set_tiles(
            sprite_item.tiles_item().create_tiles((u8)_type)
        );
    }

    /**
     * @brief Call this every frame
     */
    void update() override {
        Entity::update(); // call the underlying Entity's update
    }

    bool collides(Block *other, bn::point possible_position) {
        return (possible_position.x() + this->bounds.first.x() < other->position.x() + other->bounds.second.x()) &&
               (possible_position.y() + this->bounds.first.y() < other->position.y() + other->bounds.second.y()) &&
               (possible_position.x() + this->bounds.second.x() > other->position.x() + other->bounds.first.x()) &&
               (possible_position.y() + this->bounds.second.y() > other->position.y() + other->bounds.first.y());
    }

    bool collides_with_wall(bn::point possible_position, Box container_bounds) {
        return (
            (possible_position.x() + this->bounds.first.x() < container_bounds.first.x())  ||
            (possible_position.y() + this->bounds.first.y() < container_bounds.first.y())  ||
            (possible_position.x() + this->bounds.second.x() > container_bounds.second.x()) ||
            (possible_position.y() + this->bounds.second.y() > container_bounds.second.y())
        );
    }

    bool collides_with_wall_cutout(bn::point possible_position, int width, int height, bn::point opening) {
        const u8 half_width = (32 >> 1) - (width >> 1);
        const u8 half_height = (32 >> 1) - (height >> 1);

        const bool left = (possible_position.x() + this->bounds.first.x() < ((opening.x() - half_width) * 8) + 4);
        BN_LOG(
            "Left ", left ? "Hits" : "Misses"
        );
        const bool top = (possible_position.y() + this->bounds.first.y() < ((opening.y() - half_height) * 8) + 16);
        BN_LOG(
            "Top ", top ? "Hits" : "Misses"
        );
        const bool right = (possible_position.x() + this->bounds.second.x() > ((opening.x() - half_width) * 8) - 4);
        BN_LOG(
            "Right ", right ? "Hits" : "Misses"
        );
        const bool bottom = (possible_position.y() + this->bounds.second.y() > ((opening.y() - half_height) * 8) - 16);
        BN_LOG(
            "Bottom ", bottom ? "Hits" : "Misses"
        );

        return (
            // Left
            left   &&
            // Top
            top  &&
            // Right
            right  &&
            // Bottom
            bottom
        );
    }

    LockedAxis locked_axis = LockedAxis::NoAxis;

    Box bounds = Box(
        {0,0},
        {0,0}
    );

private:
    BlockType _type = BlockType::BlockType_DoubleWideY;
};

#endif
