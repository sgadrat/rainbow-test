#include "src/message.h"

#include <stdint.h>
#include "lib/rainbow.h"
#include "lib/nes_registers.h"
#include "lib/memory.h"

extern uint8_t last_msg_value;
uint8_t hello_sent;

void msg_set_protocol() {
	static uint8_t const cmd_set_protocol[] = {
		2, TOESP_MSG_SERVER_SET_PROTOCOL, ESP_PROTOCOL_UDP
	};
	esp_send_cmd(cmd_set_protocol);

	// Init state
	hello_sent = 0;
}

uint8_t msg_get_message() {
	if (!hello_sent) {
		static uint8_t const cmd_send_hello[] = {
			6, TOESP_MSG_SERVER_SEND_MESSAGE, 'h', 'e', 'l', 'l', 'o'
		};
		esp_send_cmd(cmd_send_hello);
		hello_sent = 1;
	}

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

	if (esp_rx_buffer[0] != 2 || esp_rx_buffer[1] != FROMESP_MSG_MESSAGE_FROM_SERVER || esp_rx_buffer[2] != oam_mirror[3]) {
		esp_rx_message_acknowledge();
		return 2;
	}
	esp_rx_message_acknowledge();
	return 1;
}
