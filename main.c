#include <stdint.h>
#include "nes_registers.h"
#include "memory.h"

// Game functions
void game_init();
void game_tick();

/////////////////////////////////////////////
// Super handy utilities
//  (Especially on 8bit hardware)
//  (Seriously, put it in a common header)
////////////////////////////////////////////

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

////////////////////////////////////
// Functions mandatorily present
//  nmi: the NMI interrupt handler
//  irq: the IRQ handler
//  main: entry point
////////////////////////////////////

/** Dumb NMI routine doing the strict minimum */
void nmi() {
	// Update OAM
	*OAMADDR = ptr_lsb(oam_mirror);
	*OAMDMA = ptr_msb(oam_mirror);

	// Ensure scroll is at X=0 Y=0
	*PPUSTATUS;
	*PPUSCROLL = 0;
	*PPUSCROLL = 0;
}

/** Dummy IRQ, we don't use it in this example */
void irq() {
}

int main() {
	*PPUCTRL = 0; // Disable NMI
	*PPUMASK = 0; // Disable rendering
	*APU_DMC_FLAGS = 0; // Disable DMC IRQs

	// First wait vblank, ensure PPU is ready
	while ((*PPUSTATUS & 0x80) == 0);

	// Move all sprites off-screen
	uint8_t i = 0;
	do {
		oam_mirror[i] = 0xff;
		++i;
	}while(i != 0);

	// Wait a second vblank
	//  PPU may need 2 frames to warm-up
	while ((*PPUSTATUS & 0x80) == 0);

	// Game specific initialization
	game_init();

	// Enable rendering
	*PPUCTRL = 0x90;
	*PPUMASK = 0x1e;

	// Game loop
	while (1) {
		game_tick();
		while ((*PPUSTATUS & 0x80) == 0);
	}
}
