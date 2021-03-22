#include <stdint.h>
#include "lib/rainbow.h"
#include "nes_registers.h"
#include "memory.h"

static uint8_t msg[100];

static void signal_error() {
	// Place error sprite at X = received value
	oam_mirror[4] = 140; // Y
	oam_mirror[5] = 4; // Tile
	oam_mirror[6] = 0; // Attributes
	oam_mirror[7] = msg[2]; // X

	// Never return
	while(1);
}

void game_init() {
	// Place progression sprite (X = expected value)
	oam_mirror[0] = 128; // Y
	oam_mirror[1] = 4; // Tile
	oam_mirror[2] = 0; // Attributes
	oam_mirror[3] = 0; // X

	// Init palettes
	static uint8_t const palettes[] = {
		// Background
		0x0f,0x0f,0x0f,0x0f, 0x0f,0x0f,0x0f,0x0f, 0x0f,0x0f,0x0f,0x0f, 0x0f,0x0f,0x0f,0x0f,
		// Sprites
		0x0f,0x20,0x20,0x20, 0x0f,0x20,0x20,0x20, 0x0f,0x20,0x20,0x20, 0x0f,0x20,0x20,0x20,
	};

	*PPUSTATUS;
	*PPUADDR = 0x3f;
	*PPUADDR = 0x00;

	for (uint8_t i = 0; i < sizeof(palettes); ++i) {
		*PPUDATA = palettes[i];
	}

	//TODO connect to server
}

void game_tick() {
	if (esp_get_msg(msg)) {
		if (msg[0] != 2 || msg[1] != FROMESP_MESSAGE_FROM_SERVER || msg[2] != oam_mirror[3]) {
			signal_error();
		}
		++oam_mirror[3];
	}
}
