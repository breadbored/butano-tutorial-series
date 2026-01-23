/*
 * Copyright (c) 2026 BreadCodes brad@bread.codes
 * Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License @ LICENSE.md file.
 */

#include "bn_core.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_items_madewithbutano.h"
#include "bn_keypad.h"

#include "types.hpp"
#include "globals.hpp"

void butano_card_scene() {

    bn::regular_bg_ptr madewithbutano = bn::regular_bg_items::madewithbutano.create_bg(0, 0);

    for (int i = 0; i < 120; i++)
    {
        if (i > 30 && bn::keypad::any_pressed()) {
            break;
        }
        bn::core::update();
    }

    scene = SceneEnum::GameScene;
    bn::core::update();
}
