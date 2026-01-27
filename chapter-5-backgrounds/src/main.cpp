/*
 * Copyright (c) 2026 BreadCodes brad@bread.codes
 * Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License @ LICENSE.md file.
 */

 #define DEBUG true

#include "bn_core.h"

#include "bn_bg_palettes.h"

#include "colors.hpp"
#include "globals.hpp"
#include "scenes.hpp"
#include "types.hpp"

SceneEnum scene = SceneEnum::TitleScene;

int main()
{
    bn::core::init();

    bn::bg_palettes::set_transparent_color(
        bread::palettes::VIVIDMEMORY8::creamy_white
    );

    while(true)
    {
        switch (scene) {
            case SceneEnum::TitleScene: {
                title_scene();
                break;
            }
            case SceneEnum::ButanoScene: {
                butano_card_scene();
                break;
            }
            case SceneEnum::GameScene: {
                game_scene();
                break;
            }
            default: {
                // default to the title scene in the event of undefined behavior
                title_scene();
                break;
            }
        }
    }
}
