#include "src/message.h"

#include <stdint.h>
#include "lib/rainbow.h"
#include "lib/nes_registers.h"
#include "lib/memory.h"

uint16_t msg_ptr;
extern uint8_t last_msg_value;

void msg_set_protocol() {
	// Do what is asked
	static uint8_t const cmd_set_protocol_tcp[] = {
		2, TOESP_MSG_SERVER_SET_PROTOCOL, ESP_PROTOCOL_TCP
	};
	esp_send_cmd(cmd_set_protocol_tcp);

	// Internal init, should have a dedicated function
	msg_ptr = 0;
	esp_rx_buffer[0] = 0;
}

uint8_t msg_get_message() {
	// If we have no buffered data, wait for a message
	if (msg_ptr == 0) {
		if (!esp_rx_message_ready()) {
			return 0;
		}

		esp_wait_tx();
		esp_tx_buffer[0] = 9;
		esp_tx_buffer[1] = TOESP_MSG_DEBUG_LOG;
		esp_tx_buffer[2] = 'r';
		esp_tx_buffer[3] = 'e';
		esp_tx_buffer[4] = 'c';
		esp_tx_buffer[5] = 'v';
		esp_tx_buffer[6] = ' ';
		esp_tx_buffer[7] = esp_rx_buffer[0];
		esp_tx_buffer[8] = esp_rx_buffer[1];
		esp_tx_buffer[9] = esp_rx_buffer[2];
		esp_tx_message_send();

		if (esp_rx_buffer[0] < 2 || esp_rx_buffer[1] != FROMESP_MSG_MESSAGE_FROM_SERVER) {
			esp_rx_message_acknowledge();
			return 2;
		}
		esp_rx_message_acknowledge();
		msg_ptr = 2;
	}

	// Check next buffered message
	last_msg_value = esp_rx_buffer[msg_ptr];
	if (last_msg_value != oam_mirror[3]) {
		return 2;
	}

	// Point on next message
	++msg_ptr;
	if (msg_ptr > esp_rx_buffer[0]) {
		msg_ptr = 0;
	}

	// Return that we have a new message
	return 1;
}
