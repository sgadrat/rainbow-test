#include "src/message.h"
#include "lib/rainbow.h"
#include "lib/nes_registers.h"
#include "lib/memory.h"
#include <stdint.h>

uint8_t last_msg_value;
uint8_t ready_state;

uint8_t const NOT_READY = 0;
uint8_t const ESP_READY = 1;
uint8_t const WIFI_READY = 2;

static void signal_error() {
	// Place error sprite at X = received value
	oam_mirror[4] = 140; // Y
	oam_mirror[5] = 1; // Tile
	oam_mirror[6] = 0; // Attributes
	oam_mirror[7] = last_msg_value; // X

	// Never return
	while(1);
}

static void connect() {
	// Connect with websocket to the preconfigured server
	static uint8_t const cmd_restore_settings[] = {
		1, TOESP_MSG_SERVER_RESTORE_SETTINGS
	};
	static uint8_t const cmd_connect[] = {
		1, TOESP_MSG_SERVER_CONNECT
	};
	esp_send_cmd(cmd_restore_settings);
	msg_set_protocol();
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
	ready_state = NOT_READY;
	static uint8_t const cmd_get_status[] = {
		1, TOESP_MSG_GET_ESP_STATUS
	};
	esp_send_cmd(cmd_get_status);
}

void game_tick() {
	if (ready_state != WIFI_READY) {
		static uint8_t const cmd_enable_wifi[] = {
			2, TOESP_MSG_WIFI_SET_CONFIG, 1
		};
		static uint8_t const cmd_get_wifi_status[] = {
			1, TOESP_MSG_WIFI_GET_STATUS
		};

		esp_wait_rx();
		switch (esp_rx_buffer[1]) {
			case FROMESP_MSG_READY:
				connect();
				ready_state = ESP_READY;
				esp_send_cmd(cmd_enable_wifi);
				esp_send_cmd(cmd_get_wifi_status);
				break;
			case FROMESP_MSG_WIFI_STATUS:
				if (esp_rx_buffer[2] == ESP_WIFI_STATUS_CONNECTED) {
					ready_state = WIFI_READY;
				}else {
					esp_send_cmd(cmd_get_wifi_status);
				}
		}
		esp_rx_message_acknowledge();
		return;
	}

	switch (msg_get_message()) {
		case 0: // No message
			break;
		case 1: // New message, OK
			++oam_mirror[3];
			break;
		case 2: // New message, incorrect
			signal_error();
	}
}
