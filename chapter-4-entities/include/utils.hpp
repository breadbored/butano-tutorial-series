/*
 * Copyright (c) 2026 BreadCodes brad@bread.codes
 * Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License @ LICENSE.md file.
 */

#ifndef BREAD_UTILS_HPP
#define BREAD_UTILS_HPP

#include "types.hpp"

static int rand_state = 8888;

int rand_from(int state);
int rand_bc(void);
int random_bits(u8 bits);
int random_bits_from(int state, u8 bits);

#endif
