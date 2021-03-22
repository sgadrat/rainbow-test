#pragma once
#include <stdint.h>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"

///////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////

// Defined message types from CPU to ESP
typedef enum toesp_cmds_t {
	// ESP CMDS
	TOESP_ESP_GET_STATUS,
	TOESP_DEBUG_GET_LEVEL,
	TOESP_DEBUG_SET_LEVEL,
	TOESP_DEBUG_LOG,
	TOESP_BUFFER_CLEAR_RX_TX,
	TOESP_BUFFER_DROP_FROM_ESP,
	TOESP_WIFI_GET_STATUS,
	TOESP_ESP_RESTART,

	// RND CMDS
	TOESP_RND_GET_BYTE,
	TOESP_RND_GET_BYTE_RANGE, // ; min / max
	TOESP_RND_GET_WORD,
	TOESP_RND_GET_WORD_RANGE, // ; min / max

	// SERVER CMDS
	TOESP_SERVER_GET_STATUS,
	TOESP_SERVER_PING,
	TOESP_SERVER_SET_PROTOCOL,
	TOESP_SERVER_GET_SETTINGS,
	TOESP_SERVER_GET_CONFIG_SETTINGS,
	TOESP_SERVER_SET_SETTINGS,
	TOESP_SERVER_RESTORE_SETTINGS,
	TOESP_SERVER_CONNECT,
	TOESP_SERVER_DISCONNECT,
	TOESP_SERVER_SEND_MSG,

	// NETWORK CMDS
	TOESP_NETWORK_SCAN,
	TOESP_NETWORK_GET_DETAILS,
	TOESP_NETWORK_GET_REGISTERED,
	TOESP_NETWORK_GET_REGISTERED_DETAILS,
	TOESP_NETWORK_REGISTER,
	TOESP_NETWORK_UNREGISTER,

	// FILE CMDS
	TOESP_FILE_OPEN,
	TOESP_FILE_CLOSE,
	TOESP_FILE_EXISTS,
	TOESP_FILE_DELETE,
	TOESP_FILE_SET_CUR,
	TOESP_FILE_READ,
	TOESP_FILE_WRITE,
	TOESP_FILE_APPEND,
	TOESP_FILE_COUNT,
	TOESP_FILE_GET_LIST,
	TOESP_FILE_GET_FREE_ID,
	TOESP_FILE_GET_INFO,
	TOESP_FILE_DOWNLOAD,
} toesp_cmds_t;

// Defined message types from ESP to CPU
typedef enum fromesp_cmds_t {
	// ESP CMDS
	FROMESP_READY,
	FROMESP_DEBUG_LEVEL,
	FROMESP_WIFI_STATUS,

	// RND CMDS
	FROMESP_RND_BYTE,
	FROMESP_RND_WORD,

	// SERVER CMDS
	FROMESP_SERVER_STATUS,
	FROMESP_SERVER_PING,
	FROMESP_SERVER_SETTINGS,
	FROMESP_MESSAGE_FROM_SERVER,

	// NETWORK CMDS
	FROMESP_NETWORK_COUNT,
	FROMESP_NETWORK_SCANNED_DETAILS,
	FROMESP_NETWORK_REGISTERED_DETAILS,
	FROMESP_NETWORK_REGISTERED,

	// FILE CMDS
	FROMESP_FILE_EXISTS,
	FROMESP_FILE_DELETE,
	FROMESP_FILE_LIST,
	FROMESP_FILE_DATA,
	FROMESP_FILE_COUNT,
	FROMESP_FILE_ID,
	FROMESP_FILE_INFO,
	FROMESP_FILE_DOWNLOAD,
} fromesp_cmds_t;

typedef enum server_protocol_t {
	PROTO_WEBSOCKET,
	PROTO_WEBSOCKET_SECURED,
	PROTO_TCP,
	PROTO_TCP_SECURED,
	PROTO_UDP,
} server_protocol_t;

typedef enum file_delete_results_t {
	FILE_DEL_SUCCESS,
	FILE_DEL_ERROR_WHILE_DELETING_FILE,
	FILE_DEL_FILE_NOT_FOUND,
	FILE_DEL_INVALID_PATH_OR_FILE,
} file_delete_results_t;

typedef enum file_download_results_t {
	FILE_DOWN_SUCCESS,
	FILE_DOWN_ERROR_WHILE_DELETING_FILE,
	FILE_DOWN_DOWNLOAD_FAILED,
	FILE_DOWN_INVALID_PATH_OR_FILE,
} file_download_results_t;

///////////////////////////////////////////////////
// Registers
///////////////////////////////////////////////////

uint8_t volatile* const RAINBOW_DATA = (uint8_t volatile* const)0x5000;
uint8_t volatile* const RAINBOW_FLAGS = (uint8_t volatile* const)0x5001;

///////////////////////////////////////////////////
// Helpers
///////////////////////////////////////////////////

/** Return true if a message from ESP is ready to be read */
static uint8_t esp_has_message() {
	return (*RAINBOW_FLAGS) & 0x80;
}

/** Read a byte from ESP, ensuring enough time passed to read the next one immediately after */
static void esp_burn_message_byte() {
	asm(
		"lda $5000\n\t"
		"nop"
		:
		:
		: "a"
	);
}

/** Send a command to the ESP
 * @param cmd pointer to the command data
 */
static void esp_send_cmd(uint8_t const* cmd) {
	uint8_t cnt = *cmd;
	uint8_t i = 1;
	*RAINBOW_DATA = cnt;
	do {
		*RAINBOW_DATA = cmd[i];
		--cnt;
	}while(cnt != 0);
}

/** Retrieve a message from ESP
 * @param dest where to write message
 * @return message length
 *
 * Message data follows the format
 *  First byte is the message length (number of bytes following this first byte).
 *  Second byte is the message type.
 *  Any remaining bytes are payload of the message.
 *
 * Note
 *  - Returns the contents of the "message length" field, so it is one less than the number
 *    of bytes writen in memory.
 *  - First byte of destination is always written (to zero if there was no message)
 *  - It is indistinguishable if there was a message with a length field of zero or there
 *    was no message.
 */
static uint8_t esp_get_msg(uint8_t* dest) {
	if (!esp_has_message()) {
		dest[0] = 0;
		return 0;
	}

	esp_burn_message_byte(); // Garbage byte
	uint8_t msg_length = *RAINBOW_DATA;
	*dest = msg_length;

	uint8_t i = 0;
	while (msg_length != 0) {
		--msg_length;
		++i;

		dest[i] = *RAINBOW_DATA;
	}

	return *dest;
}

#pragma GCC diagnostic pop
