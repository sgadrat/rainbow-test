#pragma once
#include <stdint.h>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"

static uint8_t u16_lsb(uint16_t val) {
    return ((int)val) & 0x00ff;
}

static uint8_t u16_msb(uint16_t val) {
    return (((int)val) >> 8) & 0x00ff;
}

static uint8_t ptr_lsb(uint8_t const* ptr) {
    return u16_lsb((uint16_t)ptr);
}

static uint8_t ptr_msb(uint8_t const* ptr) {
    return u16_msb((uint16_t)ptr);
}

#pragma GCC diagnostic pop
