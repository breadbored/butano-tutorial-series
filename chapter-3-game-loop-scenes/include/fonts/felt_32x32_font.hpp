//
// Auto-generated Butano font header
//

#ifndef FELT_32X32_FONT_HPP
#define FELT_32X32_FONT_HPP

#include "bn_sprite_font.h"
#include "bn_sprite_items_felt32x32.h"
#include "bn_utf8_characters_map.h"
namespace fonts {
constexpr bn::utf8_character felt_32x32_sprite_font_utf8_characters[] = {
    "Á", "É", "Í", "Ó", "Ú", "Ü", "Ñ", "á", "é", "í", "ó", "ú", "ü", "ñ", "¡", "¿"
};

constexpr signed char felt_32x32_sprite_font_character_widths[] = {
    8, // 32  
    7, // 33 !
    9, // 34 \"
    15, // 35 #
    12, // 36 $
    14, // 37 %
    11, // 38 &
    6, // 39 \'
    8, // 40 (
    8, // 41 )
    11, // 42 *
    10, // 43 +
    6, // 44 ,
    10, // 45 -
    6, // 46 .
    10, // 47 /
    11, // 48 0
    8, // 49 1
    11, // 50 2
    11, // 51 3
    11, // 52 4
    11, // 53 5
    11, // 54 6
    11, // 55 7
    11, // 56 8
    11, // 57 9
    6, // 58 :
    6, // 59 ;
    8, // 60 <
    10, // 61 =
    8, // 62 >
    10, // 63 ?
    14, // 64 @
    11, // 65 A
    11, // 66 B
    11, // 67 C
    11, // 68 D
    11, // 69 E
    9, // 70 F
    11, // 71 G
    12, // 72 H
    6, // 73 I
    9, // 74 J
    12, // 75 K
    11, // 76 L
    15, // 77 M
    13, // 78 N
    12, // 79 O
    11, // 80 P
    12, // 81 Q
    11, // 82 R
    11, // 83 S
    11, // 84 T
    12, // 85 U
    11, // 86 V
    14, // 87 W
    12, // 88 X
    12, // 89 Y
    11, // 90 Z
    8, // 91 [
    10, // 92 [backslash]
    8, // 93 ]
    9, // 94 ^
    10, // 95 _
    5, // 96 `
    9, // 97 a
    9, // 98 b
    9, // 99 c
    9, // 100 d
    9, // 101 e
    9, // 102 f
    10, // 103 g
    11, // 104 h
    7, // 105 i
    6, // 106 j
    11, // 107 k
    6, // 108 l
    12, // 109 m
    11, // 110 n
    9, // 111 o
    10, // 112 p
    10, // 113 q
    10, // 114 r
    9, // 115 s
    9, // 116 t
    10, // 117 u
    10, // 118 v
    14, // 119 w
    10, // 120 x
    10, // 121 y
    9, // 122 z
    9, // 123 {
    6, // 124 |
    9, // 125 }
    12, // 126 ~
    11, // Á
    11, // É
    7, // Í
    12, // Ó
    12, // Ú
    12, // Ü
    13, // Ñ
    9, // á
    9, // é
    7, // í
    9, // ó
    10, // ú
    10, // ü
    11, // ñ
    7, // ¡
    10, // ¿
};

constexpr bn::span<const bn::utf8_character> felt_32x32_sprite_font_utf8_characters_span(
    felt_32x32_sprite_font_utf8_characters
);

constexpr auto felt_32x32_sprite_font_utf8_characters_map =
    bn::utf8_characters_map<felt_32x32_sprite_font_utf8_characters_span>();

constexpr bn::sprite_font felt_32x32_sprite_font(
    bn::sprite_items::felt32x32, felt_32x32_sprite_font_utf8_characters_map.reference(),
    felt_32x32_sprite_font_character_widths
);
}
#endif //FELT_32X32_FONT_HPP
