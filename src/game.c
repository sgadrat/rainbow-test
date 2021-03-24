#include <stdint.h>
#include "lib/rainbow.h"
#include "lib/nes_registers.h"
#include "lib/memory.h"

uint8_t msg[100]; //FIXME should be static, needs this to fixed https://github.com/itszor/gcc-6502-bits/issues/11

static void signal_error() {
	// Place error sprite at X = received value
	oam_mirror[4] = 140; // Y
	oam_mirror[5] = 1; // Tile
	oam_mirror[6] = 0; // Attributes
	oam_mirror[7] = msg[2]; // X

	// Never return
	while(1);
}

static void connect() {
	// Connect with websocket to the preconfigured server
	static uint8_t const cmd_restore_settings[] = {
		1, TOESP_SERVER_RESTORE_SETTINGS
	};
	static uint8_t const cmd_set_protocol_ws[] = {
		2, TOESP_SERVER_SET_PROTOCOL, PROTO_WEBSOCKET
	};
	static uint8_t const cmd_connect[] = {
		1, TOESP_SERVER_CONNECT
	};
	esp_send_cmd(cmd_restore_settings);
	esp_send_cmd(cmd_set_protocol_ws);
	esp_send_cmd(cmd_connect);
}

void game_init() {
	// Place progression sprite (X = expected value)
	oam_mirror[0] = 128; // Y
	oam_mirror[1] = 1; // Tile
	oam_mirror[2] = 0; // Attributes
	oam_mirror[3] = 0; // X

	// Init palettes
	static uint8_t const palettes[] = {
		// Background
		0x0f,0x0f,0x0f,0x0f, 0x0f,0x0f,0x0f,0x0f, 0x0f,0x0f,0x0f,0x0f, 0x0f,0x0f,0x0f,0x0f,
		// Sprites
		0x0f,0x00,0x10,0x20, 0x0f,0x20,0x20,0x20, 0x0f,0x20,0x20,0x20, 0x0f,0x20,0x20,0x20,
	};

	*PPUSTATUS;
	*PPUADDR = 0x3f;
	*PPUADDR = 0x00;

	for (uint8_t i = 0; i < sizeof(palettes); ++i) {
		*PPUDATA = palettes[i];
	}

	// Ping ESP to be notified when it's ready
	static uint8_t const cmd_get_status[] = {
		1, TOESP_ESP_GET_STATUS
	};
	esp_send_cmd(cmd_get_status);
}

void game_tick() {
	if (esp_get_msg(msg)) {
		if (msg[0] == 1 && msg[1] == FROMESP_READY) {
			connect();
		}else {
			if (msg[0] != 2 || msg[1] != FROMESP_MESSAGE_FROM_SERVER || msg[2] != oam_mirror[3]) {
				signal_error();
			}
			++oam_mirror[3];
		}
	}
}
