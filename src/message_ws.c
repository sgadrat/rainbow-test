#include "src/message.h"

#include <stdint.h>
#include "lib/rainbow.h"
#include "lib/nes_registers.h"
#include "lib/memory.h"

extern uint8_t last_msg_value;

void msg_set_protocol() {
	static uint8_t const cmd_set_protocol_ws[] = {
		2, TOESP_MSG_SERVER_SET_PROTOCOL, ESP_PROTOCOL_WEBSOCKET
	};
	esp_send_cmd(cmd_set_protocol_ws);
}

uint8_t msg_get_message() {
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

	last_msg_value = esp_rx_buffer[2];

	if (esp_rx_buffer[0] != 2 || esp_rx_buffer[1] != FROMESP_MSG_MESSAGE_FROM_SERVER || esp_rx_buffer[2] != oam_mirror[3]) {
		esp_rx_message_acknowledge();
		return 2;
	}
	esp_rx_message_acknowledge();
	return 1;
}
