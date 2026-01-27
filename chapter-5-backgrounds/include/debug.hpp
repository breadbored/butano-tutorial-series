/*
 * Copyright (c) 2026 BreadCodes brad@bread.codes
 * Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License @ LICENSE.md file.
 */

#ifndef BREAD_DEBUG_HPP
#define BREAD_DEBUG_HPP

#ifndef DEBUG
    #define DEBUG false
#else
    // If DEBUG is set and true, we can turn on logging in the mGBA emulator
    #if DEBUG
        #define BN_CFG_LOG_ENABLED true
        #define BN_CFG_LOG_BACKEND BN_LOG_BACKEND_MGBA
    #endif
#endif
// `BN_CFG_LOG_ENABLED` will determine if logging is enabled or not through `BN_LOG`
#include "bn_log.h"

#endif
