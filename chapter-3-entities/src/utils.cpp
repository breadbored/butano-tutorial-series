#include "utils.hpp"

int rand_from(int state) {
    int x = state;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 5;
    return x;
}

int rand_bc(void) {
    return rand_state = rand_from(rand_state);
}

int random_bits(u8 bits) {
    return (rand_bc() & ((1 << bits) - 1));
}

int random_bits_from(int state, u8 bits) {
    return (rand_from(state) & ((1 << bits) - 1));
}
