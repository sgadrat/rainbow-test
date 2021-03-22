#pragma once
#include <stdint.h>

// Object Attribute Memory mirror, where we store sprites info to be copied to the PPU memory during vblank
static uint8_t* const oam_mirror = (uint8_t*)0x0200;
