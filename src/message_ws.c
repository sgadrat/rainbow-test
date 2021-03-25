#include "src/message.h"

#include <stdint.h>
#include "lib/rainbow.h"
#include "lib/nes_registers.h"
#include "lib/memory.h"

uint8_t msg[100]; //FIXME should be static, needs this to fixed https://github.com/itszor/gcc-6502-bits/issues/11
extern uint8_t last_msg_value;

void msg_set_protocol() {
	static uint8_t const cmd_set_protocol_ws[] = {
		2, TOESP_SERVER_SET_PROTOCOL, PROTO_WEBSOCKET
	};
	esp_send_cmd(cmd_set_protocol_ws);
}

uint8_t msg_get_message() {
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

	last_msg_value = msg[2];

	if (msg[0] != 2 || msg[1] != FROMESP_MESSAGE_FROM_SERVER || msg[2] != oam_mirror[3]) {
		return 2;
	}
	return 1;
}
