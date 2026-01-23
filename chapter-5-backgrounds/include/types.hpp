/*
 * Copyright (c) 2026 BreadCodes brad@bread.codes
 * Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License @ LICENSE.md file.
 *
 * Thank you to TONC for providing these definitions
 * //! \file tonc_types.h
 * //! \author J Vijn
 * //! \date 20060508 - 20080111
 */

#ifndef BREAD_TYPES_HPP
#define BREAD_TYPES_HPP

#include "tonc_types.h"
#include "bn_utility.h"
#include "bn_point.h"

typedef unsigned int uint, eint;
typedef unsigned short ushort, eshort;

typedef uint8_t u8, byte, uchar, echar;
typedef uint16_t u16, hword;
typedef uint32_t u32, word;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef volatile u64 vu64;

typedef volatile s8 vs8;
typedef volatile s16 vs16;
typedef volatile s32 vs32;
typedef volatile s64 vs64;

typedef const u8 cu8;
typedef const u16 cu16;
typedef const u32 cu32;
typedef const u64 cu64;

typedef const s8 cs8;
typedef const s16 cs16;
typedef const s32 cs32;
typedef const s64 cs64;

enum SceneEnum : u8 {
    TitleScene = 0,
    ButanoScene = 1,
    GameScene = 2,
};

enum LockedAxis : u8 {
    NoAxis = 0,
    XAxis = 1,
    YAxis = 2,
    BothAxis = 3,
};

enum BlockType : u8 {
    BlockType_DoubleWideY = 0,
    BlockType_DoubleWideX = 1,
    BlockType_SingleWideY = 2,
    BlockType_SingleWideX = 3,
    BlockType_BigSquare   = 4,
};

typedef bn::pair<bn::point, bn::point> Box;
typedef bn::pair<BlockType, bn::point> LevelPair; // this is a shorthand for the level structure

#endif
