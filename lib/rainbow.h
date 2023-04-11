#pragma once

#include "utils.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"

static uint8_t const TOESP_MSG_GET_ESP_STATUS = 0;   // Get ESP status
static uint8_t const TOESP_MSG_DEBUG_GET_LEVEL = 1;   // Get debug level
static uint8_t const TOESP_MSG_DEBUG_SET_LEVEL = 2;   // Set debug level
static uint8_t const TOESP_MSG_DEBUG_LOG = 3;   // Debug / Log data
static uint8_t const TOESP_MSG_CLEAR_BUFFERS = 4;   // Clear RX/TX buffers
static uint8_t const TOESP_MSG_FROMESP_MSG_BUFFER_DROP_FROM_ESP = 5;   // Drop messages from TX (ESP->outside world) buffer
static uint8_t const TOESP_MSG_ESP_GET_FIRMWARE_VERSION = 6;   // Get Rainbow firmware version
static uint8_t const TOESP_MSG_ESP_RESTART = 7;   // Restart ESP
static uint8_t const TOESP_MSG_WIFI_GET_STATUS = 8;   // Get WiFi connection status
static uint8_t const TOESP_MSG_WIFI_GET_SSID = 9;   // Get WiFi network SSID
static uint8_t const TOESP_MSG_WIFI_GET_IP = 10;  // Get WiFi IP address
static uint8_t const TOESP_MSG_WIFI_GET_CONFIG = 11; // Get WiFi / Access Point / Web Server config
static uint8_t const TOESP_MSG_WIFI_SET_CONFIG = 12; // Set WiFi / Access Point / Web Server config
static uint8_t const TOESP_MSG_AP_GET_SSID = 13;  // Get Access Point network SSID
static uint8_t const TOESP_MSG_AP_GET_IP = 14;  // Get Access Point IP address
static uint8_t const TOESP_MSG_RND_GET_BYTE = 15;  // Get random byte
static uint8_t const TOESP_MSG_RND_GET_BYTE_RANGE = 16;  // Get random byte between custom min/max
static uint8_t const TOESP_MSG_RND_GET_WORD = 17;  // Get random word
static uint8_t const TOESP_MSG_RND_GET_WORD_RANGE = 18;  // Get random word between custom min/max
static uint8_t const TOESP_MSG_SERVER_GET_STATUS = 19;  // Get server connection status
static uint8_t const TOESP_MSG_SERVER_PING = 20;  // Get ping between ESP and server
static uint8_t const TOESP_MSG_SERVER_SET_PROTOCOL = 21;  // Set protocol to be used to communicate (WS/UDP)
static uint8_t const TOESP_MSG_SERVER_GET_SETTINGS = 22;  // Get current server host name and port
static uint8_t const TOESP_MSG_SERVER_GET_CONFIG_SETTINGS = 23;  // Get server host name and port defined in the Rainbow config file
static uint8_t const TOESP_MSG_SERVER_SET_SETTINGS = 24;  // Set current server host name and port
static uint8_t const TOESP_MSG_SERVER_RESTORE_SETTINGS = 25;  // Restore server host name and port to values defined in the Rainbow config
static uint8_t const TOESP_MSG_SERVER_CONNECT = 26;  // Connect to server
static uint8_t const TOESP_MSG_SERVER_DISCONNECT = 27;  // Disconnect from server
static uint8_t const TOESP_MSG_SERVER_SEND_MESSAGE = 28;  // Send message to server
static uint8_t const TOESP_MSG_NETWORK_SCAN = 29;  // Scan networks around and return count
static uint8_t const TOESP_MSG_NETWORK_GET_SCANNED_DETAILS = 30;  // Get scanned network details
static uint8_t const TOESP_MSG_NETWORK_GET_REGISTERED = 31;  // Get registered networks status
static uint8_t const TOESP_MSG_NETWORK_GET_REGISTERED_DETAILS = 32;  // Get registered network SSID
static uint8_t const TOESP_MSG_NETWORK_REGISTER = 33;  // Register network
static uint8_t const TOESP_MSG_NETWORK_UNREGISTER = 34;  // Unregister network
static uint8_t const TOESP_MSG_NETWORK_SET_ACTIVE = 35;  // Set active network
static uint8_t const TOESP_MSG_FILE_OPEN = 36;  // Open working file
static uint8_t const TOESP_MSG_FILE_CLOSE = 37;  // Close working file
static uint8_t const TOESP_MSG_FILE_STATUS = 38;  // Get working file status
static uint8_t const TOESP_MSG_FILE_EXISTS = 39;  // Check if file exists
static uint8_t const TOESP_MSG_FILE_DELETE = 40;  // Delete a file
static uint8_t const TOESP_MSG_FILE_SET_CUR = 41;  // Set working file cursor position a file
static uint8_t const TOESP_MSG_FILE_READ = 42;  // Read working file (at specific position)
static uint8_t const TOESP_MSG_FILE_WRITE = 43;  // Write working file (at specific position)
static uint8_t const TOESP_MSG_FILE_APPEND = 44;  // Append data to working file
static uint8_t const TOESP_MSG_FILE_COUNT = 45;  // Count files in a specific path
static uint8_t const TOESP_MSG_FILE_GET_LIST = 46;  // Get list of existing files in a path
static uint8_t const TOESP_MSG_FILE_GET_FREE_ID = 47;  // Get an unexisting file ID in a specific path
static uint8_t const TOESP_MSG_FILE_GET_INFO = 48;  // Get file info (size + crc32)
static uint8_t const TOESP_MSG_FILE_DOWNLOAD = 49;  // Download a file from a giving URL to a specific path index / file index
static uint8_t const TOESP_MSG_FILE_FORMAT = 50;  // Format file system
static uint8_t const FROMESP_MSG_READY = 0;   // ESP is ready
static uint8_t const FROMESP_MSG_DEBUG_LEVEL = 1;   // Returns debug configuration
static uint8_t const FROMESP_MSG_ESP_FIRMWARE_VERSION = 2;   // Returns the Rainbow firmware version
static uint8_t const FROMESP_MSG_WIFI_STATUS = 3;   // Returns WiFi connection status
static uint8_t const FROMESP_MSG_SSID = 4;   // WiFi/AccessPoint SSID
static uint8_t const FROMESP_MSG_IP_ADDRESS = 5;   // WiFi/AccessPoint IP address
static uint8_t const FROMESP_MSG_WIFI_CONFIG = 6;   // Returns WiFi config
static uint8_t const FROMESP_MSG_RND_BYTE = 7;   // Returns random byte value
static uint8_t const FROMESP_MSG_RND_WORD = 8;   // Returns random word value
static uint8_t const FROMESP_MSG_SERVER_STATUS = 9;   // Returns server connection status
static uint8_t const FROMESP_MSG_SERVER_PING = 10;  // Returns min, max and average round-trip time and number of lost packets
static uint8_t const FROMESP_MSG_SERVER_SETTINGS = 11;  // Returns server settings (host name + port)
static uint8_t const FROMESP_MSG_MESSAGE_FROM_SERVER = 12;  // Message from server
static uint8_t const FROMESP_MSG_NETWORK_COUNT = 13;  // Returns number of networks found
static uint8_t const FROMESP_MSG_NETWORK_SCANNED_DETAILS = 14;  // Returns details for a scanned network
static uint8_t const FROMESP_MSG_NETWORK_REGISTERED_DETAILS = 15;  // Returns SSID for a registered network
static uint8_t const FROMESP_MSG_NETWORK_REGISTERED = 16;  // Returns registered networks status
static uint8_t const FROMESP_MSG_FILE_STATUS = 17;  // Returns the working file status
static uint8_t const FROMESP_MSG_FILE_EXISTS = 18;  // Returns if file exists or not
static uint8_t const FROMESP_MSG_FILE_DELETE = 19;  // Returns when trying to delete a file
static uint8_t const FROMESP_MSG_FILE_LIST = 20;  // Returns path file list (FILE_GET_LIST)
static uint8_t const FROMESP_MSG_FILE_DATA = 21;  // Returns file data (FILE_READ)
static uint8_t const FROMESP_MSG_FILE_COUNT = 22;  // Returns file count in a specific path
static uint8_t const FROMESP_MSG_FILE_ID = 23;  // Returns a free file ID (FILE_GET_FREE_ID)
static uint8_t const FROMESP_MSG_FILE_INFO = 24;  // Returns file info (size + CRC32) (FILE_GET_INFO)
static uint8_t const FROMESP_MSG_FILE_DOWNLOAD = 25;  // Returns download result code
static uint8_t const ESP_PROTOCOL_WEBSOCKET = 0;
static uint8_t const ESP_PROTOCOL_WEBSOCKET_SECURED = 1;
static uint8_t const ESP_PROTOCOL_TCP = 2;
static uint8_t const ESP_PROTOCOL_TCP_SECURED = 3;
static uint8_t const ESP_PROTOCOL_UDP = 4;
static uint8_t const ESP_WIFI_STATUS_IDLE_STATUS = 0;
static uint8_t const ESP_WIFI_STATUS_NO_SSID_AVAIL = 1;
static uint8_t const ESP_WIFI_STATUS_SCAN_COMPLETED = 2;
static uint8_t const ESP_WIFI_STATUS_CONNECTED = 3;
static uint8_t const ESP_WIFI_STATUS_CONNECT_FAILED = 4;
static uint8_t const ESP_WIFI_STATUS_CONNECTION_LOST = 5;
static uint8_t const ESP_WIFI_STATUS_WRONG_PASSWORD = 6;
static uint8_t const ESP_WIFI_STATUS_DISCONNECTED = 7;
static uint8_t const ESP_FILE_PATH_SAVE = 0;
static uint8_t const ESP_FILE_PATH_ROMS = 1;
static uint8_t const ESP_FILE_PATH_USER = 2;
static uint8_t const ESP_FILE_MODE_AUTO = 0;
static uint8_t const ESP_FILE_MODE_MANUAL = 1;
static uint8_t const ESP_FILE_DELETE_SUCCESS = 0;
static uint8_t const ESP_FILE_DELETE_ERROR_WHILE_DELETING_FILE = 1;
static uint8_t const ESP_FILE_DELETE_FILE_NOT_FOUND = 2;
static uint8_t const ESP_FILE_DELETE_INVALID_PATH_OR_FILE = 3;
static uint8_t const ESP_FILE_DOWNLOAD_SUCCESS = 0; // Success (HTTP status in 2xx)
static uint8_t const ESP_FILE_DOWNLOAD_INVALID_DESTINATION = 1; // Invalid destination (path/filename)
static uint8_t const ESP_FILE_DOWNLOAD_ERROR_WHILE_DELETING_FILE = 2; // Error while deleting existing file
static uint8_t const ESP_FILE_DOWNLOAD_UNKNOWN_PROTOCOL = 3; // Unknown / unsupported protocol
static uint8_t const ESP_FILE_DOWNLOAD_NETWORK_ERROR = 4; // Network error
static uint8_t const ESP_FILE_DOWNLOAD_HTTP_ERROR = 5; // HTTP status is not in 2xx
static uint8_t const ESP_FILE_DOWNLOAD_NETWORK_ERROR_CONNECTION_FAILED = 255; // Connection failed
static uint8_t const ESP_FILE_DOWNLOAD_NETWORK_ERROR_SEND_HEADER_FAILED = 254; // Send header failed
static uint8_t const ESP_FILE_DOWNLOAD_NETWORK_ERROR_SEND_PAYLOAD_FILED = 253; // Send payload failed
static uint8_t const ESP_FILE_DOWNLOAD_NETWORK_ERROR_NOT_CONNECTED = 252; // Not connected
static uint8_t const ESP_FILE_DOWNLOAD_NETWORK_ERROR_CONNECTION_LOST = 251; // Connection lost
static uint8_t const ESP_FILE_DOWNLOAD_NETWORK_ERROR_NO_STREAM = 250; // No stream
static uint8_t const ESP_FILE_DOWNLOAD_NETWORK_ERROR_NO_HTTP_SERVER = 249; // No HTTP server
static uint8_t const ESP_FILE_DOWNLOAD_NETWORK_ERROR_OUT_OF_RAM = 248; // Too less RAM
static uint8_t const ESP_FILE_DOWNLOAD_NETWORK_ERROR_ENCODING = 247; // Encoding
static uint8_t const ESP_FILE_DOWNLOAD_NETWORK_ERROR_STREAM_WRITE = 246; // Stream write
static uint8_t const ESP_FILE_DOWNLOAD_NETWORK_ERROR_READ_TIMEOUT = 245; // Read timeout
static uint8_t const ESP_MSG_SIZE = 0;
static uint8_t const ESP_MSG_TYPE = 1;
static uint8_t const ESP_MSG_PAYLOAD = 2;

////////////////////////////////////
// Registers
////////////////////////////////////

extern uint8_t volatile RAINBOW_WIFI_RX;
extern uint8_t volatile RAINBOW_WIFI_TX;

////////////////////////////////////
// Buffers
////////////////////////////////////

static uint8_t* const esp_rx_buffer = (uint8_t* const)0x4800;
static uint8_t* const esp_tx_buffer = (uint8_t* const)0x4900;

////////////////////////////////////
// Utility functions that have no asm counterpart
////////////////////////////////////

static bool esp_tx_ready() {
	return (RAINBOW_WIFI_TX & 0x80) != 0;
}

static void esp_wait_tx() {
	while(!esp_tx_ready()) {
	}
}

static bool esp_rx_message_ready() {
	return (RAINBOW_WIFI_RX & 0x80) != 0;
}

static void esp_wait_rx() {
	while(!esp_rx_message_ready()) {
	}
}

static void esp_rx_message_acknowledge() {
	RAINBOW_WIFI_RX = 0;
}

static void esp_tx_message_send() {
	RAINBOW_WIFI_TX = 0;
}

static void esp_wait_answer(uint8_t type) {
	uint8_t* const rx = esp_rx_buffer;

	bool found = false;
	while(!found) {
		esp_wait_rx();
		if (rx[ESP_MSG_TYPE] != type) {
			esp_rx_message_acknowledge();
		}else {
			found = true;
		}
	}
}

static void esp_set_server_settings(uint16_t port, char const* host) {
	uint8_t const host_len = strnlen8(host, 200); // Lil' bit below 256 because ESP message headers + port information

	esp_wait_tx();

	uint8_t* const buff = esp_tx_buffer;
	buff[0] = host_len + 3;
	buff[1] = TOESP_MSG_SERVER_SET_SETTINGS;
	buff[2] = u16_msb(port);
	buff[3] = u16_lsb(port);
	memcpy(buff+4, (uint8_t*)host, host_len);

	esp_tx_message_send();
}

static void esp_file_close() {
	uint8_t* const tx = esp_tx_buffer;

	esp_wait_tx();
	tx[0] = 1;
	tx[1] = TOESP_MSG_FILE_CLOSE;
	esp_tx_message_send();
}

static bool esp_file_exists(uint8_t path, uint8_t file) {
	uint8_t* const tx = esp_tx_buffer;
	uint8_t* const rx = esp_rx_buffer;

	esp_wait_tx();
	tx[0] = 4;
	tx[1] = TOESP_MSG_FILE_EXISTS;
	tx[2] = ESP_FILE_MODE_AUTO;
	tx[3] = path;
	tx[4] = file;
	esp_tx_message_send();

	esp_wait_answer(FROMESP_MSG_FILE_EXISTS);
	bool exists = rx[ESP_MSG_PAYLOAD];
	esp_rx_message_acknowledge();

	return exists;
}

static void esp_file_open(uint8_t path, uint8_t file) {
	uint8_t* const tx = esp_tx_buffer;

	esp_wait_tx();
	tx[0] = 4;
	tx[1] = TOESP_MSG_FILE_OPEN;
	tx[2] = ESP_FILE_MODE_AUTO;
	tx[3] = path;
	tx[4] = file;
	esp_tx_message_send();
}

static uint8_t esp_file_read(uint8_t* dest, uint8_t count) {
	uint8_t* const tx = esp_tx_buffer;
	uint8_t* const rx = esp_rx_buffer;

	esp_wait_tx();
	tx[0] = 2;
	tx[1] = TOESP_MSG_FILE_READ;
	tx[2] = count;
	esp_tx_message_send();

	esp_wait_answer(FROMESP_MSG_FILE_DATA);
	uint8_t n_read = rx[ESP_MSG_PAYLOAD+0];
	memcpy(dest, rx+ESP_MSG_PAYLOAD+1, n_read);
	esp_rx_message_acknowledge();

	return n_read;
}

static void esp_file_write(uint8_t* src, uint8_t count) {
	uint8_t* const tx = esp_tx_buffer;

	esp_wait_tx();
	tx[0] = count + 1;
	tx[1] = TOESP_MSG_FILE_WRITE;
	memcpy(tx+2, src, count);
	esp_tx_message_send();
}

static void esp_send_cmd(uint8_t const* cmd) {
	uint8_t* const tx = esp_tx_buffer;

	esp_wait_tx();
	for (uint8_t n = 0; n <= cmd[0]; ++n) {
		tx[n] = cmd[n];
	}
	esp_tx_message_send();
}

static void dbg_show_rx_buffer() {
	esp_wait_tx();
    esp_tx_buffer[0] = 7;
    esp_tx_buffer[1] = TOESP_MSG_DEBUG_LOG;
    esp_tx_buffer[2] = 'r';
    esp_tx_buffer[3] = 'x';
    esp_tx_buffer[6] = ' ';
    esp_tx_buffer[7] = esp_rx_buffer[0];
    esp_tx_buffer[8] = esp_rx_buffer[1];
    esp_tx_buffer[9] = esp_rx_buffer[2];
    esp_tx_message_send();
}

#pragma GCC diagnostic pop
