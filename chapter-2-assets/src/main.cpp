/*
 * Copyright (c) 2026 BreadCodes brad@bread.codes
 * MIT License @ LICENSE.md file.
 */

// Your main.cpp should always import `bn_core.h`
// See `bn::core::init();` in the `main` function
#include "bn_core.h"

// Sprites
#include "bn_bg_palettes.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"

// Data Structures
#include "bn_vector.h"
#include "bn_string.h"

// A font I am including for you to use
#include "felt_32x32_font.hpp"

// A color palette & utility header I made for this series
#include "colors.hpp"

int main()
{
    // Initialize Butano
    // This is how every game should start
    bn::core::init();

    // Set the color of the screen when a background doesn't cover that section
    bn::bg_palettes::set_transparent_color(
        bread::palettes::ColdfireGB::neutral_salmon
    );

    // Create the text generator, using the font of our choice
    bn::sprite_text_generator text_generator(
        // font
        fonts::felt_32x32_sprite_font,
        // optionally define a palette for color
        bread::palettes::ColdfireGB::sprite_palette_item
    );

    // and let's put the positional anchor in the center of the text
    text_generator.set_center_alignment();

    // Butano uses bn::string for strings
    bn::string<15> title_message_string = "Getting Started";

    // Create a vector that has at least 1 slot for every expected character in the string
    // I will set the string length to exactly how many I need for a static string
    bn::vector<bn::sprite_ptr, 15> title_message_sprites;

    // We can use `title_message_string` to fill `title_message_sprites` vector
    text_generator.generate(
        0, -16,
        title_message_string,
        title_message_sprites
    );

    // We can make a new vector and fill it for another line
    bn::string<9> subtitle_message_string = "Chapter 1";
    bn::vector<bn::sprite_ptr, 9> subtitle_message_sprites;
    text_generator.generate(
        0, 16,
        subtitle_message_string,
        subtitle_message_sprites
    );

    // Now, so long as `title_message_sprites` exists in the scope*, the message will persist on the screen
    //  * We will cover scopes in a later chapter

    // The main game loop.
    while(true)
    {
        // Render the frame
        bn::core::update();
    }
}
