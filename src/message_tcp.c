#include "src/message.h"

#include <stdint.h>
#include "lib/rainbow.h"
#include "lib/nes_registers.h"
#include "lib/memory.h"

uint8_t msg[257]; //FIXME should be static, needs this to fixed https://github.com/itszor/gcc-6502-bits/issues/11
uint16_t msg_ptr;
extern uint8_t last_msg_value;

void msg_set_protocol() {
	// Do what is asked
	static uint8_t const cmd_set_protocol_tcp[] = {
		2, TOESP_SERVER_SET_PROTOCOL, PROTO_TCP
	};
	esp_send_cmd(cmd_set_protocol_tcp);

	// Internal init, should have a dedicated function
	msg_ptr = 0;
	msg[0] = 0;
}

uint8_t msg_get_message() {
	// If we have no buffered data, wait for a message
	if (msg_ptr == 0) {
		if (!esp_get_msg(msg)) {
			return 0;
		}

		*RAINBOW_DATA = 9;
		*RAINBOW_DATA = TOESP_DEBUG_LOG;
		*RAINBOW_DATA = 'r';
		*RAINBOW_DATA = 'e';
		*RAINBOW_DATA = 'c';
		*RAINBOW_DATA = 'v';
		*RAINBOW_DATA = ' ';
		*RAINBOW_DATA = msg[0];
		*RAINBOW_DATA = msg[1];
		*RAINBOW_DATA = msg[2];

		if (msg[0] < 2 || msg[1] != FROMESP_MESSAGE_FROM_SERVER) {
			return 2;
		}
		msg_ptr = 2;
	}

	// Check next buffered message
	last_msg_value = msg[msg_ptr];
	if (last_msg_value != oam_mirror[3]) {
		return 2;
	}

	// Point on next message
	++msg_ptr;
	if (msg_ptr > msg[0]) {
		msg_ptr = 0;
	}

	// Return that we have a new message
	return 1;
}
